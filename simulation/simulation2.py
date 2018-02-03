import pymunk
import pygame
from pygame.constants import *

SCREEN_DIM = 720


class Simulation:
    """
    Main simulation object
    Use this to run the simulation
    """

    def __init__(self):
        self.screen = pygame.display.set_mode((SCREEN_DIM, SCREEN_DIM))
        self.robot = Robot()
        self.field = Field()
        self.fps = 30
        self.space = pymunk.Space()
        self.running = False

    def run(self):
        self.running = True
        while self.running:


    def loop(self):
        for event in pygame.event.get():
            if event.type == QUIT:
                self.not_running = True

        self.robot.loop()
        self.field.loop()


class Field:
    """
    Simulation object for the field
    Includes boundaries
    """

    def __init__(self, size, screen, space):
        self.screen = screen
        self.size = size
        self.body = pymunk.Body(body_type=pymunk.Body.STATIC)
        self.space = space
        # Other initialization stuff (adding the segments, others)

    def loop(self):
        pass

    def draw(self):
        pass


class Robot:
    """
    Simulation object for the Robot
    Can be controlled
    """

    def __init__(self, size, screen, space):
        self.screen = screen
        self.size = size
        self.mass = 10
        self.moment = pymunk.moment_for_box(self.mass, self.size)
        self.body = pymunk.Body(self.mass, self.moment)
        # Other initialization stuff (shape, others)

    def loop(self):
        """
        This function is called every loop.
        It runs the logic, then the draw function.
        """

    def draw(self):
        """
        Main drawing function for the robot.
        """


if __name__ == "__main__":
    pass
