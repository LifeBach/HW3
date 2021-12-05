#include "headers.h"
#include "parser.h"

/*****************************************************************************
*   Operator overload: implement
*****************************************************************************/

ostream  &operator<<(ostream &os, const Block &block)
{
    os << block.name << ":"<<" len: "<<block.len <<" height: "<<block.height<<" x: "<<block.coord.x<<" y: "<<block.coord.y<<endl;
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

int numNets;
int numPins;
vector<Net> net_list;

/*****************************************************************************
*   Function: implement
*****************************************************************************/

void Block::rotate()
{
    this->is_rotate = !this->is_rotate;
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

void net_parser(char *filename)
{
    FILE *fp; 
    fp = fopen(filename,"r");
    char name_temp[20];
    string temp_name;
    fscanf(fp,"NumNets : %d\n",&numNets);
    fscanf(fp,"NumPins : %d\n",&numPins);
    for(int j=0; j<numNets; j++)
    {
        Net net;
        fscanf(fp,"NetDegree : %d\n", &net.degree);
        for (int i=0; i<net.degree; i++)
        {
            fscanf(fp,"%s\n", name_temp);
            temp_name = name_temp;
            net.netlist.push_back(temp_name);
        }
        net_list.push_back(net);
    }
}

int Net::hpwl()
{
    int x_max = 0;
    int x_min = 99999999;
    int y_max = 0;
    int y_min = 99999999;
    for (auto it = netlist.begin(); it != netlist.end(); it++)
    {
        if (block_hash.find(*it) != block_hash.end())
        {
            if(block_hash[*it].coord.x + (0.5 * block_hash[*it].len) > x_max)
            {
                x_max = block_hash[*it].coord.x + (0.5 * block_hash[*it].len);
            }
            if(block_hash[*it].coord.y + (0.5 * block_hash[*it].height) > y_max)
            {
                y_max = block_hash[*it].coord.y + (0.5 * block_hash[*it].height);
            }
            if(block_hash[*it].coord.x + (0.5 * block_hash[*it].len) < x_min)
            {
                x_min = block_hash[*it].coord.x + (0.5 * block_hash[*it].len);
            }
            if(block_hash[*it].coord.y + (0.5 * block_hash[*it].height) < y_min)
            {
                y_min = block_hash[*it].coord.y + (0.5 * block_hash[*it].height);
            }
        }
        else if(terminal_hash.find(*it) != terminal_hash.end())
        {
            if(terminal_hash[*it].coord.x > x_max)
            {
                x_max = terminal_hash[*it].coord.x;
            }
            if(terminal_hash[*it].coord.y > y_max)
            {
                y_max = terminal_hash[*it].coord.y;
            }
            if(terminal_hash[*it].coord.x < x_min)
            {
                x_min = terminal_hash[*it].coord.x;
            }
            if(terminal_hash[*it].coord.y < y_min)
            {
                y_min = terminal_hash[*it].coord.y;
            }
        }
    }
    return (x_max-x_min)+(y_max-y_min);
}