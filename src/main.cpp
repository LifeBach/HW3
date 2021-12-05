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
    clock_t io_start, io_end;
    clock_t build_start, build_end;
    clock_t find_start, find_end;
    clock_t optimize_start, optimize_end;

    //Parser
    io_start=clock();
    block_parser(block_file);
    terminal_parser(terminal_file);
    net_parser(net_file);
    io_end=clock();
    cout<< "io_time: "<<(double)(io_end - io_start)/CLOCKS_PER_SEC<<endl; 

    //create constraint
    Constraint constraint(block_area, dead_space_ratio);
    cout << "constraint width: "<< constraint.get_max_width()<<"constraint height: "<< constraint.get_max_height()<<endl;
    
    //build init B* Tree
    build_start = clock();
    bst.build(constraint);
    bst.packing(constraint);
    bst.wirelen_cal();
    build_end = clock();
    cout<< "build_time: "<<(double)(build_end - build_start)/CLOCKS_PER_SEC<<endl; 
    cout << "init: "<<"width:"<<bst.width <<"height:"<<bst.height << " wirelen: "<< bst.wirelength<<endl;
    
    //find base result (satisfy constraint)
    find_start = clock();
    bst.find_init_result(constraint);
    bst.packing(constraint);
    bst.wirelen_cal();
    find_end = clock();
    cout<< "find_time: "<<(double)(find_end - find_start)/CLOCKS_PER_SEC<<endl; 
    cout << "constraint_satisfy: "<<"width:"<<bst.width <<"height:"<<bst.height << " wirelen: "<< bst.wirelength<<endl;

    //optimize wirelength
    int optimize_limit = 1000 - (double)(find_end - find_start)/CLOCKS_PER_SEC - (double)(build_end - build_start)/CLOCKS_PER_SEC - (double)(io_end - io_start)/CLOCKS_PER_SEC;
    optimize_start = clock();
    bst.greedy_wirelen(constraint,optimize_limit);
    bst.packing(constraint);
    bst.wirelen_cal();
    optimize_end = clock();
    cout<<"optimize_time: "<< (double)(optimize_end - optimize_start)/CLOCKS_PER_SEC<<endl;
    cout << "greedy_wire_length_optimize: "<<"width:"<<bst.width <<"height:"<<bst.height << " wirelen: "<< bst.wirelength<<endl;

    out_floorplan(output_file, bst);
}