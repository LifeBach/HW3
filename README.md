# HW3: FloorPlan
## Introduction
In this homework, you are asked to implement an existing algorithm or develop your own algorithm to solve the fixed-outline floorplan design problem with a set of hard blocks.

## Problem Description
### Input
- A set **_B_** of hard blocks, where each block **_b<sub>i<sub>_** in **_B_** has a rectangular shape specified by 4 corners.
- A netlist **_E_**
- The dead space ratio, which is predefined and passed by the argument. The aspect ratio of the floorplan region is 1, so you can calculate the width  **_w<sub>fl<sub>_** and height  **_h_** of the floorplan region as follows:
 
w<sub>_fl_<sub> = h<sub>_fl_<sub> = sqrt((_total block area_ * (1 + (_dead space ratio_))))

For example, if the total block area is 1100000 and the dead space ratio is 0.1, the width _w<sub>fl<sub>_ and height _h<sub>fl<sub>_ of the floorplanning region are as follows:
