#include "headers.h"
#include "parser.h"
#include "floorplan_core.h"

/*****************************************************************************
*   Main function
*****************************************************************************/
int main(int argc, char *argv[])
{
    char *block_file = argv[1];
    char *net_file = argv[2];
    char *terminal_file = argv[3];
    char *output_file = argv[4];
    float dead_space_ratio = stof(argv[5]);
    //Parser
    block_parser(block_file);
    terminal_parser(terminal_file);
    //create constraint
    Constraint constraint(block_area, dead_space_ratio);
    //build init B* Tree
    bst.build(constraint);
    // auto max = max_element(begin(bst.contour),end(bst.contour)); 
    // int max_h = *max;
    // cout <<"curr_height:" << max_h << "constraint: "<< constraint.get_max_height()<<endl;
    bst.traverse(bst.root);
}