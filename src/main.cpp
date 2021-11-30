#include "headers.h"
#include "parser.h"
#include "floorplan_core.h"
/*****************************************************************************
*   Global variable
*****************************************************************************/

int numBlocks;
vector<string> block_name; //block_hash:key
unordered_map<string, Block> block_hash;
int block_area;

int numTerminals;
vector<string> terminal_name; //terminal_hash:key
unordered_map<string, Terminal> terminal_hash;

Constraint constraint;

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
    constraint.set_constraint(block_area, dead_space_ratio);

}