#ifndef FLOORPLAN_CORE_H
#define FLOORPLAN_CORE_H

/*****************************************************************************
*   structure
*****************************************************************************/

struct Constraint
{
    public:
        Constraint(): max_height(0), max_width(0) {};
        Constraint(const int area, const float dead_space_ratio);
        int get_max_height();
        int get_max_width();
        bool is_satisfy(float width, float height);
    private:
        int max_height;
        int max_width;
};

struct BStarT_node
{
    BStarT_node *left_child;
    BStarT_node *right_child; 
    BStarT_node *parent;
    Block *block;
    int degree;
    int level;
    BStarT_node(): left_child(NULL), right_child(NULL), parent(NULL){};
    BStarT_node(Block *pBlock);
};

struct BStarT
{
    float width;
    float height;
    float area;
    int wirelength;
    BStarT_node *root;
    unordered_map<string, BStarT_node*> node_hash;
    vector<int> contour;
    BStarT(): width(0), height(0), area(0), wirelength(0) {};
    void build(Constraint &constraint);
    void packing(Constraint &constraint);
    void block_swap(string block_name_1, string block_name_2);
    void block_rotate(string block_name);
    void traverse(BStarT_node *curr_node);
    float cost(float alpha, float beta);
    void find_init_result(Constraint &constraint);
    void greedy_wirelen(Constraint &constraint, int time_limit);
    void wirelen_cal();
};

/*****************************************************************************
*   Global variable: declaration
*****************************************************************************/

extern Constraint constraint;
extern BStarT bst;
extern vector<int> contour;
extern unsigned int seed;

/*****************************************************************************
*   operator overload: declaration
*****************************************************************************/

ostream  &operator<<(ostream &os, const BStarT_node* &bst_node);

/*****************************************************************************
*   function: declaration
*****************************************************************************/
void out_floorplan(char *filename, BStarT tree);
#endif