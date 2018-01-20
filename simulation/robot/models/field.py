import pymunk
import pygame.image
import pygame.transform
import os
from .. import ROOT_DIR
import math


class Field:
    def __init__(self, space, size=(800, 800)):
        self.mass = math.inf
        self.body = pymunk.Body(self.mass, pymunk.moment_for_box(self.mass, size))
        self.box = pymunk.Poly.create_box(self.body)
        self.body.position = (400, 400)
        space.add(self.body)
        self.size = size

    def __convert__(self, screen, position):
        _, y = screen.get_size()
        return position.x, y - position.y

    def draw(self, screen):
        pos = self.__convert__(screen, self.box.body.position)
        angle = math.degrees(self.body.angle) + 180

        screen.blit(rotated_image, offset_pos)
