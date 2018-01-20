import pygame
from pygame.locals import *
from pygame.color import *
from pygame.color import *
from robot.models import Robot, Field
import pymunk.pygame_util
import pygame.display
import pygame.time

import pygame
import pymunk


class Simulation:

    def __init__(self):
        self.running = True
        self.width = 1080
        self.height = 720
        self.screen = pygame.display.set_mode((self.width, self.height))
        self.clock = pygame.time.Clock()
        self.fps = 30

        self.draw_options = pymunk.pygame_util.DrawOptions(self.screen)
        pygame.display.set_caption("Robotics Simulation")

        self.space = pymunk.Space()

        self.robot = Robot(self.space)
        self.field = Field(self.space)

        self.space.gravity = (0, 0)

    def loop(self):
        for event in pygame.event.get():
            # handle events here
            if event.type == QUIT:
                self.running = False
        self.draw()

    def run(self):
        while self.running:
            self.loop()

        pygame.quit()

    def draw(self):
        self.screen.fill(THECOLORS["white"])
        self.space.step(1 / self.fps)
        self.space.debug_draw(self.draw_options)

        self.robot.draw(self.screen)
        pygame.display.flip()
        self.clock.tick(self.fps)


if __name__ == "__main__":
    simulation = Simulation()
    simulation.run()
