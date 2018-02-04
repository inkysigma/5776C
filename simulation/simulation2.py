import pymunk
import pygame
import math
from pygame.constants import *

SCREEN_DIM = 720
ROBOT_SIZE = (60, 60)
FIELD_SIZE = SCREEN_DIM, SCREEN_DIM
FPS = 30
IMAGE_FILENAME = "resources/robot2.png"


class Simulation:
    """
    Main simulation object
    Use this to run the simulation
    """

    def __init__(self, fps=FPS, robot_size=ROBOT_SIZE, field_size=FIELD_SIZE):
        self.screen = pygame.display.set_mode((SCREEN_DIM, SCREEN_DIM))
        self.space = pymunk.Space()
        self.robot = Robot(robot_size, self.screen, self.space)
        self.field = Field(field_size, self.screen, self.space)
        self.fps = fps
        self.space.gravity = 0, 0
        self.clock = pygame.time.Clock()
        self.running = False

    def run(self):
        self.running = True
        while self.running:
            self.loop()
        pygame.quit()

    def loop(self):
        events = pygame.event.get()
        for event in events:
            if event.type == QUIT:
                self.running = False
            if event.type == K_ESCAPE:
                self.running = False

        self.screen.fill((255, 255, 255))
        self.robot.loop(events)
        self.robot.draw()
        self.field.draw()
        self.space.step(1/self.fps)
        self.clock.tick(self.fps)


class Field:
    """
    Simulation object for the field
    Includes boundaries
    """

    def __init__(self, size, screen, space):
        self.screen = screen
        self.size = size
        self.space = space
        self.vertices = [[0, 0], [0, self.size[0]], size, [self.size[0], 0]]
        # Other initialization stuff (adding the segments, others)
        # Note: Segment should be with elasticity zero
        # self.bodies = [pymunk.Body(body_type=pymunk.Body.STATIC) for i in self.vertices]
        self.segments = []
        for num, pt in enumerate(self.vertices):
            self.segments.append(pymunk.Segment(self.space.static_body, pt, self.vertices[num - 1], 2))

        for seg in self.segments:
            seg.elasticity = 0.25
            space.add(seg)

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
        self.shape = pymunk.Poly.create_box(self.body, self.size, 0)  # Last argument is radius
        self.img = pygame.image.load(IMAGE_FILENAME)
        self.img = pygame.transform.scale(self.img, size)
        # Other initialization stuff (shape, others)

    def loop(self, events):
        """
        This function is called every loop.
        It runs the logic.
        """

    def draw(self):
        """
        Main drawing function for the robot.
        Note: hitbox may be different than display
        """
        angle_degrees = math.degrees(self.body.angle) + 180
        rotated_img = pygame.transform.rotate(self.img, angle_degrees)
        self.screen.blit(rotated_img, self.body.position)


if __name__ == "__main__":
    simulation = Simulation()
    simulation.run()
