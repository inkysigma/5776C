import pymunk
import pygame.image
import os
from .. import ROOT_DIR


class Robot:
    def __init__(self, space, size=(20, 20)):
        self.mass = 10
        self.body = pymunk.Body(self.mass, pymunk.moment_for_box(self.mass, size))
        self.box = pymunk.Poly.create_box(self.body)
        space.add(self.body)
        self.image = pygame.image.load(os.path.join(ROOT_DIR, "resources/robot.png"))

    def __convert(self, screen, position):
        return (position.x, screen.height - position.y)

    def draw(self, screen):
        pos = self.box.body.position
