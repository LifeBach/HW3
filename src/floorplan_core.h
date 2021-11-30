#ifndef FLOORPLAN_CORE_H
#define FLOORPLAN_CORE_H

/*****************************************************************************
*   structure
*****************************************************************************/

struct Constraint
{
    public:
        Constraint(): max_height(0), max_width(0) {};
        void set_constraint(const int area, const float dead_space_ratio);
        int get_max_height();
        int get_max_width();
    private:
        int max_height;
        int max_width;
};

/*****************************************************************************
*   Global variable: declaration
*****************************************************************************/

extern Constraint constraint;

/*****************************************************************************
*   operator overload: declaration
*****************************************************************************/


/*****************************************************************************
*   function: declaration
*****************************************************************************/

#endif