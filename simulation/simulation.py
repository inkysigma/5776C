import pymunk
import pygame
import math
from pygame.constants import *

SCREEN_DIM = 720
ROBOT_SIZE = (60, 60)
FIELD_SIZE = SCREEN_DIM, SCREEN_DIM
FPS = 60
ROBOT_FILENAME = "resources/robot2.png"
ROBOT_EXTENDED = "resources/robot_extended.png"
ROBOT_MOGO = "resources/robot_mogo.png"
ROBOT_EXTENDED_MOGO = "resources/robot_mogo_extended.png"
BACKGROUND_FILENAME = "resources/background.png"
SPEED_COEFFICIENT = 100
ANG_VELOCITY_COEFFICIENT = 1.5
CONE_RADIUS = 20
MOGO_RADIUS = 30
ROBOT_COLLISION_TYPE = 13
CONE_COLLISION_TYPE = 14
RED = 0
BLUE = 1


class Simulation:
    """
    Main simulation object
    Use this to run the simulation
    """

    def __init__(self, fps=FPS, robot_size=ROBOT_SIZE, field_size=FIELD_SIZE):
        self.screen = pygame.display.set_mode((SCREEN_DIM, SCREEN_DIM))
        pygame.display.set_caption("Simulation")
        self.space = pymunk.Space()
        self.space.damping = 0.0001
        self.robot = Robot(robot_size, self.screen, self.space)
        self.field = Field(field_size, self.screen, self.space)
        self.background = pygame.image.load(BACKGROUND_FILENAME)
        self.background = pygame.transform.scale(self.background, FIELD_SIZE)
        self.cones = [Cone(CONE_RADIUS, self.screen, self.space, (x * 50, 420)) for x in range(5)]
        self.mogos = [MobileGoal(MOGO_RADIUS, self.screen, self.space, (x * 50, 500)) for x in range(5)]
        self.col_handler = self.space.add_collision_handler(ROBOT_COLLISION_TYPE, CONE_COLLISION_TYPE)
        self.set_collision_handler(self.col_handler)
        print(self.col_handler.begin)
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

        # self.screen.fill((255, 255, 255))
        self.screen.blit(self.background, (0, 0))
        self.robot.loop(events)
        self.robot.draw()
        for cone in self.cones:
            cone.loop()
            cone.draw()
        for mogo in self.mogos:
            mogo.loop()
            mogo.draw()
        self.space.step(1/self.fps)
        self.clock.tick(self.fps)
        pygame.display.update()

    @staticmethod
    def set_collision_handler(handler):
        def begin(arbiter, space, data):
            print("Collision began")
            point = arbiter.contact_point_set.points[0].point_a
            if
            return True

        def pre_solve(arbiter, space, data):
            print("Pre-solve is running")
            return True

        def post_solve(arbiter, space, data):
            print("post-solve is running")
            return True

        handler.begin = begin
        handler.post_solve = post_solve
        handler.pre_solve = pre_solve


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
        self.segments = []
        for num, pt in enumerate(self.vertices):
            self.segments.append(pymunk.Segment(self.space.static_body, pt, self.vertices[num - 1], 2))

        for seg in self.segments:
            self.space.add(seg)


class Robot:
    """
    Simulation object for the Robot
    Can be controlled
    """

    def __init__(self, size, screen, space, pos=(int(SCREEN_DIM/2), int(SCREEN_DIM/2))):
        self.screen = screen
        self.size = size
        self.mass = 10
        self.space = space
        self.moment = pymunk.moment_for_box(self.mass, self.size)
        self.body = pymunk.Body(self.mass, self.moment)
        self.body.position = pos
        self.translated_pos = self.body.position
        self.shape = pymunk.Poly.create_box(self.body, self.size, 0)  # Last argument is radius
        self.shape.collision_type = ROBOT_COLLISION_TYPE
        self.img = pygame.image.load(ROBOT_FILENAME)
        self.img = pygame.transform.scale(self.img, size)
        self.img = self.img.convert_alpha()
        self.forwards = 0
        self.sideways = 0
        self.old_position = self.body.position
        self.space.add(self.shape, self.body)
        self.mogo_out = False
        self.claw_out = False
        # Other initialization stuff (shape, others)

    def loop(self, events):
        """
        This function is called every loop.
        It runs the logic.
        """
        for event in events:
            if event.type == KEYDOWN:
                if event.key == K_w:
                    self.forwards = -1
                if event.key == K_s:
                    self.forwards = 1
                if event.key == K_a:
                    self.sideways = 1
                if event.key == K_d:
                    self.sideways = -1
                if event.key == K_SPACE:
                    self.mogo_out = False if self.mogo_out else True
                if event.key == K_e:
                    self.claw_out = False if self.claw_out else True

            elif event.type == KEYUP:
                if (event.key == K_w and self.forwards == -1) or (event.key == K_s and self.forwards == 1):
                    self.forwards = 0
                if (event.key == K_a and self.sideways == 1) or (event.key == K_d and self.sideways == -1):
                    self.sideways = 0
        self.body.velocity = (math.cos(math.pi/2 - self.body.angle) * SPEED_COEFFICIENT * self.forwards,
                              math.sin(math.pi/2 - self.body.angle) * SPEED_COEFFICIENT * self.forwards)
        self.body.angular_velocity = self.sideways * ANG_VELOCITY_COEFFICIENT

    def draw(self):
        """
        Main drawing function for the robot.
        Note: hit box may be different than displayed
        """
        angle_degrees = math.degrees(self.body.angle) + 180
        rotated_img = pygame.transform.rotate(self.img, angle_degrees)
        # Translates image so image doesn't move position when it rotates (it's a bit shaky though)
        self.translated_pos = self.body.position
        self.translated_pos[0] -= round(rotated_img.get_width()/2)
        self.translated_pos[1] -= round(rotated_img.get_height()/2)
        self.screen.blit(rotated_img, self.translated_pos)


class Cone:
    def __init__(self, radius, screen, space, pos):
        self.space = space
        self.screen = screen
        self.radius = radius
        self.mass = 10
        self.moment = pymunk.moment_for_circle(self.mass, 0, self.radius)
        self.body = pymunk.Body(self.mass, self.moment)
        self.body.position = pos
        self.shape = pymunk.Circle(self.body, self.radius)
        self.shape.collision_type = CONE_COLLISION_TYPE
        self.space.add(self.body, self.shape)

    def loop(self):
        pass

    def draw(self):
        pygame.draw.circle(self.screen, (128, 127, 0), (int(self.body.position[0]), int(self.body.position[1])),
                           int(self.radius))


class MobileGoal:
    def __init__(self, radius, screen, space, pos, mogo_type=RED):
        self.space = space
        self.screen = screen
        self.radius = radius
        self.mass = 10
        self.moment = pymunk.moment_for_circle(self.mass, 0, self.radius)
        self.body = pymunk.Body(self.mass, self.moment)
        self.body.position = pos
        self.shape = pymunk.Circle(self.body, self.radius)
        self.space.add(self.body, self.shape)
        self.type = mogo_type if mogo_type == 0 or mogo_type == 1 else 0

    def loop(self):
        pass

    def draw(self):
        # Main circle
        pygame.draw.circle(self.screen, (255, 0, 0), (int(self.body.position[0]), int(self.body.position[1])),
                           int(self.radius))
        # Circle border
        pygame.draw.circle(self.screen, (0, 0, 0), (int(self.body.position[0]), int(self.body.position[1])),
                           int(self.radius), 2)


if __name__ == "__main__":
    simulation = Simulation()
    simulation.run()
