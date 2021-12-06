# HW3: FloorPlan
## Introduction
In this homework, you are asked to implement an existing algorithm or develop your own algorithm to solve the fixed-outline floorplan design problem with a set of hard blocks.

## Problem Description
### Input
- A set $\B$ of hard blocks, where each block $b_i$ in $\B$ has a rectangular shape specified by 4 corners.
- A netlist 𝐸
- The dead space ratio, which is predefined and passed by the argument. The aspect ratio of the floorplan region is 1, so you can calculate the width 𝑤 𝑓𝑙
𝑤 = h 𝑓𝑙 𝑓𝑙
and height h of the floorplan region as follows:
