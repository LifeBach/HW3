#ifndef PARSER_H
#define PARSER_H
/*****************************************************************************
*   Structure
*****************************************************************************/
struct Coordinate
{
    int x;
    int y;
};

struct Block
{
    string name;
    Coordinate coord;
    int len;
    int height;
    bool is_rotate;
    void rotate();
};

struct Terminal
{
    string name;
    Coordinate coord;
};

/*****************************************************************************
*   Global variable: declaration
*****************************************************************************/
extern float dead_space_ratio;

extern int numBlocks;
extern vector<string> block_name; //hash key
extern unordered_map<string, Block> block_hash;
extern int block_area;

extern int numTerminals;
extern vector<string> terminal_name; //hash key
extern unordered_map<string, Terminal> terminal_hash;

/*****************************************************************************
*   Operator overload: declaration
*****************************************************************************/

ostream  &operator<<(ostream &os, const Block &block);
ostream  &operator<<(ostream &os, const Terminal &terminal);

/*****************************************************************************
*   Function: declaration
*****************************************************************************/

void block_parser(char * file_name);
void terminal_parser(char *filename);

#endif

