Field:
    vertices: (0, 0), (0, SCREEN_DIM), (SCREEN_DIM, SCREEN_DIM), (SCREEN_DIM, 0)
Robot:

Gravity: (0, 0)

Mobile Goal intake has two states:
* compact
* extended
    * when moving from compact to extended, it increases in size over a specified period of time (i. e. one second)
    * while increasing in size, it pushes all objects out of the way
    * if the robot drives into the mobile goal, then it stays on top of it
    * if the mobile goal is on top of the robot right before it is converted to compact, the robot successfully retrieved the cone


Claw has 4 states:
* extended open
    * the displayed size is bigger than the actual size
    * if a single cone is in front of the center of the robot, then it can be picked up with the key "E"
    
* extended closed
    * same as compact, except it has a bigger size
    * slowly increases in size of a period of time (i. e. one second)
    
* compact
    * compact open or closed doesn't matter
    * default position
    * default size
    * cannot grab cones
    
y = mx + b
-1/m