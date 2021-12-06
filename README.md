# HW3: FloorPlan
## Introduction
In this homework, you are asked to implement an existing algorithm or develop your own algorithm to solve the fixed-outline floorplan design problem with a set of hard blocks.

## Problem Description
### Input
- A set **_B_** of hard blocks, where each block **_b<sub>i<sub>_** in **_B_** has a rectangular shape specified by 4 corners.
- A netlist **_E_**
- The dead space ratio, which is predefined and passed by the argument. The aspect ratio of the floorplan region is 1, so you can calculate the width  **_w<sub>fl<sub>_** and height  **_h_** of the floorplan region as follows:
  
  **_w<sub>fl<sub>_** = **_h<sub>fl<sub>_** = sqrt((_total block area_ * (1 + (_dead space ratio_))))
 
  For example, if the total block area is 1100000 and the dead space ratio is 0.1, the width _w<sub>fl<sub>_ and height _h<sub>fl<sub>_ of the floorplanning region are as follows:
  **_w<sub>fl<sub>_** = **_h<sub>fl<sub>_** = sqrt(1100000 * 1.1) = 1100
  Then, the coordinates of the lower-left corner and upper-right corner of the floorplan region are (0, 0) and (**_w<sub>fl<sub>_** , **_h<sub>fl<sub>_**), respectively.
 
### Output
The total wirelength of all nets, where the wirelength for each net is defined as the half-perimeter wirelength (HPWL) of the minimum bounding box of pins of the net. Each pin of block **_b<sub>i<sub>_** is located at the center of **_b<sub>i<sub>_**. Note that the **x-** or **y-** coordinate, say **_i_**, of each block center is rounded down to an integer **_k_** such that **_k_** ≤ **_i_** ≤ **_k_** + 1.
