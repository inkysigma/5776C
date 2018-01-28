import pymunk
import pygame
from pygame.locals import *
import pymunk.pygame_util

FPS = 60
FIELD_DIM = 600

ROBOT_SIZE = (100, 100)


def main():
    pygame.init()
    screen = pygame.display.set_mode((FIELD_DIM, FIELD_DIM))
    pygame.display.set_caption("Simulation")
    clock = pygame.time.Clock()
    space = pymunk.Space()
    space.gravity = (0, 0)
    draw_options = pymunk.pygame_util.DrawOptions(screen)

    robot_body, robot_shape = add_robot(space, (int(FIELD_DIM/2), int(FIELD_DIM/2)))

    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                exit()
            elif event.type == KEYDOWN:
                if event.key == K_ESCAPE:
                    pygame.quit()
                    exit()
                if event.key == K_w:
                    # Move forwards
                    pass
                elif event.key == K_s:
                    # Move backwards
                    pass
                if event.key == K_d:
                    # Move right
                    pass
                elif event.key == K_a:
                    # Move left
                    pass

        space.step(1/FPS)

        screen.fill((255, 255, 255))
        space.debug_draw(draw_options)

        pygame.display.flip()
        clock.tick(FPS)


def add_robot(space, coords):
    mass = 1000
    moment = pymunk.moment_for_box(mass, ROBOT_SIZE)
    body = pymunk.Body(mass, moment)
    body.position = coords
    shape = pymunk.Poly.create_box(body, ROBOT_SIZE)
    space.add(body, shape)
    return body, shape


if __name__ == "__main__":
    exit(main())
