#include "headers.h"
#include "parser.h"
#include "floorplan_core.h"


/*****************************************************************************
*   Operator overload: implement
*****************************************************************************/

/*****************************************************************************
*   Function: implement
*****************************************************************************/

void Constraint::set_constraint(const int area, const float dead_space_ratio)
{
    max_height = sqrt(area * (1+(dead_space_ratio)));
    max_width = sqrt(area * (1+(dead_space_ratio)));
}

int Constraint::get_max_height()
{
    return max_height;
}

int Constraint::get_max_width()
{
    return max_width;
}

void create_tree()
{
    
}
