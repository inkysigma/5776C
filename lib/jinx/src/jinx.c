#include "JINX.h"
#include "main.h"

#define MSG "Hello JINX!"

static FILE *comPort = stdout;

void initJINX(FILE *port) {
  // If the port is not a valid communications port, inform user of error
  if (!setComPort(port)) {
    // Would print to stderr, but not set for PROS
    printf("Invalid Port specified for JINX communications\n");

    // Optionally allow user to fail on error. Not recommended
    // exit(EXIT_FAILURE);
  }
}

bool setComPort(FILE *port) {
  // If the port is either of the UARTs, set up the pins correctly for serial
  // data
  if (port == uart1 || port == uart2) {
    usartInit(port, 115200, SERIAL_8N1);
    return true;

    // Port is set to STDOUT by default, but still allow users to specify it if
    // they wish.
  } else if (port == stdout) {
    return true;
  }

#if (DEBUG_JINX)
  printf("Failed to open specified port for JINX (setComPort(FILE* port))\n");
#endif

  return false;
}

void JINXRun(void *ignore) {
  int del = 500;
  JINX inStr;
  inStr.command = NULL;
  inStr.token = NULL;
  // setOpmode(1);
  // Read the garbage. Assume run before serial communications open
  delay(1000);
  while (fcount(comPort) > 0) {
    fgetc(comPort);
    writeJINXSerial("Trashing garbage\n");
  };
  writeJINXSerial("finished trashing garbage\n");

  while (true) {
    writeJINXMessage("Should wait for new string");

    // Get message, save in inStr, then parse.
    readLine(&inStr);
    parseMessage(&inStr);
    delay(del);
  }
}

void writeJINXSerial(const char *message) {
  fprintf(comPort, "%s%s%s%s", JINX_HEADER, JINX_DELIMETER, message,
          JINX_TERMINATOR);
  fflush(comPort);
}

// Wrapper function for writeJINXData to send non-numeric data more easily
void writeJINXMessage(const char *message) { writeJINXData("msg", message); }

void writeJINXData(const char *name, const char *value) {
  // if (strlen(name) + strlen(value) >= MAX_MESSAGE_SIZE + PROTOCOL_SIZE) {
  //     fprintf(comPort, "Warning: Tried to send too large a message named %s",
  //     name);
  //     return;
  // }

  char message[100];
  sprintf(message, "%s%s%s", name, JINX_DELIMETER, value);
  writeJINXSerial(message);
}

//*************This space reserved for user-defined functions***************
// Example of user defined JINX helper function.
// Since it is at the top of this file, it can be called from anywhere else in
// this file.
// Good practice is to put its prototype in JINX.h, though.
void handleGet(JINX *inStr) {
  // Get the first token from the sent command
  getToken(inStr, 1);

  // Host outgoing messages
  char *message = (char *)malloc(sizeof(char) * (strlen(inStr->token) + 30));
  if (strcmp(inStr->token, "DEBUG_JINX") == 0) {
    writeJINXMessage("Asked for Debug");
    sprintf(message, "%s, %d", inStr->token, DEBUG_JINX);
  } else {
    sprintf(message, "%s %s", inStr->token, " was unable to be gotten.");
  }

  // Free malloc'd string
  writeJINXMessage(message);
  free(message);
  message = NULL;
}

// Returns positive integer parsed from character buffer
int parseInt(const char *intString) {
  char digit;

  // Limit to 32 digit integer. Please don't send 32 digit integers
  char tempStr[33] = "";

  int len = strlen(intString);

  // Catch empty string
  if (len == 0) {
    char errorMessage[100];
    sprintf(errorMessage, "Error, unable to parse integer: %s", intString);
    writeJINXData("Error ", errorMessage);
  }

  for (int i = 0; i < len; i++) {
    digit = intString[i];
    if ((digit < '0') || (digit > '9')) {
      char errorMessage[100];
      sprintf(errorMessage, "Error, unable to parse integer: %s", intString);
      writeJINXData("Error", errorMessage);
      return -1;
    }

    tempStr[i] = digit;
  }

  return atoi(tempStr);
}
//**************************************************************************

// Example parse. User can and should replace with own body.
void parseMessage(JINX *inStr) {
  // Echo entire recieved message
  writeJINXMessage(inStr->command);
  // Set inStr->token to first token (space-delimated word)
  getToken(inStr, 0);

  if (strcmp(inStr->token, "Option_1") == 0) {
    // Do option 1
    writeJINXMessage("Option 1 chosen.");
  } else if (strcmp(inStr->token, "get") == 0) {
    // Call another function to handle "get"
    handleGet(inStr);
  } else {
    // Do default
    writeJINXMessage("No comparison found");
  }
}
