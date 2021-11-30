#include "headers.h"
#include "parser.h"

/*****************************************************************************
*   Operator overload: implement
*****************************************************************************/

ostream  &operator<<(ostream &os, const Block &block)
{
    os << block.name << ":"<<" len: "<<block.len <<" height: "<<block.height<<endl;
    return os;
}

ostream  &operator<<(ostream &os, const Terminal &terminal)
{
    os << terminal.name << ":"<<" x: "<<terminal.coord.x <<" y: "<<terminal.coord.y<<endl;
    return os;
}

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

/*****************************************************************************
*   Function: implement
*****************************************************************************/

void Block::rotate()
{
    is_rotate = 1;
    swap(len,height);
}

void block_parser(char *filename)
{
    FILE *fp; 
    fp = fopen(filename,"r");
    Block block;
    int x,y,w,h,t;
    char name_temp[20];
    fscanf(fp,"NumHardRectilinearBlocks : %d\n",&numBlocks);
    fscanf(fp,"NumTerminals : %d\n\n",&numTerminals);
    for (int i=0; i<numBlocks; i++)
    {
        fscanf(fp,"%s hardrectilinear 4 (%d, %d) (%d, %d) (%d, %d) (%d, %d)\n",name_temp,&x,&y,&t,&t,&w,&h,&t,&t);
        block.name = name_temp;
        block.len = w - x;
        block.height = h - y;
        block.is_rotate = 0;
        block_area += block.len * block.height;
        block_name.push_back(block.name);
        block_hash.insert(make_pair(block.name,block));
        memset(name_temp, 0, sizeof(name_temp));
    }
}

void terminal_parser(char *filename)
{
    FILE *fp; 
    fp = fopen(filename,"r");
    Terminal terminal;
    char name_temp[20];
    int x;
    int y;
    for (int i=0; i<numTerminals; i++)
    {
        fscanf(fp,"%s	%d	%d\n",&name_temp, &x, &y);
        terminal.name = name_temp;
        terminal.coord.x = x;
        terminal.coord.y = y;
        terminal_name.push_back(terminal.name);
        terminal_hash.insert(make_pair(terminal.name,terminal));
    }
}