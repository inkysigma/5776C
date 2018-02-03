import pymunk
import pygame.image
import pygame.transform
from pygame.color import *


class Field:
    def __init__(self, space, size=(800, 800)):
        self.mass = 10000000
        segment_vertexes = [
            ((10, 10), (10, 660)),
            ((10, 660), (660, 660)),
            ((660, 660), (660, 10)),
            ((660, 10), (10, 10))
        ]
        self.segments = []
        for a, b in segment_vertexes:
            body = pymunk.Body()
            segment = pymunk.Segment(body, a, b, 2)
            self.segments.append(segment)
            space.add(segment)
        self.size = size
        self.rectangle = pygame.Rect(10, 10, 650, 650)

    @staticmethod
    def _convert(screen, position):
        _, y = screen.get_size()
        return position.x, y - position.y

    def draw(self, screen):
        pygame.draw.rect(screen, THECOLORS["grey"], self.rectangle, 0)
        for segment in self.segments:
            pygame.draw.line(screen, THECOLORS["black"], segment.a, segment.b, 2)


class Cone:
    pass


class MobileGoal:
    pass


