import pymunk
import pygame.image
import pygame.transform
import os
from .. import ROOT_DIR
import math


class Robot:
    def __init__(self, space, size=(60, 60)):
        self.mass = 10
        self.body = pymunk.Body(self.mass, pymunk.moment_for_box(self.mass, size))
        self.box = pymunk.Poly.create_box(self.body)
        self.body.position = (150, 150)
        space.add(self.body)
        self.image = pygame.image.load(os.path.join(ROOT_DIR, "resources/robot.png"))
        self.size = size

    def __convert__(self, screen, position):
        _, y = screen.get_size()
        return position.x, y - position.y

    def draw(self, screen):
        pos = self.__convert__(screen, self.box.body.position)
        angle = math.degrees(self.body.angle) + 180
        rotated_image = pygame.transform.scale(pygame.transform.rotate(self.image, angle), self.size)

        offset = pymunk.Vec2d(rotated_image.get_size()) / 2
        offset_pos = pos - offset

        screen.blit(rotated_image, offset_pos)

    def apply_left_impulse(self, impulse):
        self.body.apply_impulse_at_local_point((0, impulse), (0, 0))
