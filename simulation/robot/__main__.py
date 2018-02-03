from pygame.locals import *
from pygame.color import *
from robot.models import Robot, Field
import pymunk.pygame_util
import pygame.display
import pygame.time

import pygame
import pymunk


class Simulation:
    def __init__(self):
        self.apply_left_impulse = False
        self.apply_right_impulse = False
        self.running = True
        self.width = 1080
        self.height = 720
        self.screen = pygame.display.set_mode((self.width, self.height))
        self.clock = pygame.time.Clock()
        self.fps = 60

        self.draw_options = pymunk.pygame_util.DrawOptions(self.screen)
        pygame.display.set_caption("Robotics Simulation")

        self.space = pymunk.Space()

        self.robot = Robot(self.space)
        self.field = Field(self.space)

        self.space.gravity = (0, 0)

    def loop(self):
        if self.apply_left_impulse:
            self.robot.apply_left_impulse(10)
        for event in pygame.event.get():
            # handle events here
            if event.type == QUIT:
                self.running = False
            elif event.type == KEYDOWN:
                if event.key == K_w:
                    self.apply_left_impulse = True
            elif event.type == KEYUP:
                if event.key == K_w:
                    self.apply_left_impulse = False
            self.draw()
        self.clock.tick(self.fps)

    def run(self):
        while self.running:
            self.loop()
        pygame.quit()

    def draw(self):
        self.screen.fill(THECOLORS["white"])
        self.space.step(1 / self.fps)
        self.field.draw(self.screen)
        self.robot.draw(self.screen)
        pygame.display.flip()


if __name__ == "__main__":
    simulation = Simulation()
    simulation.run()
