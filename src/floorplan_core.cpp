#include "headers.h"
#include "parser.h"
#include "floorplan_core.h"

/*****************************************************************************
*   Global variable: declaration
*****************************************************************************/

BStarT bst;
unsigned int seed = 1638714618;//(unsigned)time(NULL);//1638623718;

/*****************************************************************************
*   Operator overload: implement
*****************************************************************************/

ostream  &operator<<(ostream &os, const BStarT_node* &bst_node)
{
    os << *(bst_node->block) <<"degree: "<<bst_node->degree<<endl;
    return os;
}

/*****************************************************************************
*   Function: implement
*****************************************************************************/

Constraint::Constraint(const int area, const float dead_space_ratio)
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

bool Constraint::is_satisfy(float width, float height)
{
    if(width <= max_width && height <= max_height)
    {
        return true;
    }
    else
    {
        return false;
    }
}

BStarT_node::BStarT_node(Block *pBlock)
{
    block = pBlock;
    left_child = NULL;
    right_child = NULL;
    parent = NULL;
    degree = 0;
    level = 0;
}

void BStarT::build(Constraint &constraint)
{
    int max_width = constraint.get_max_width();
    int max_height = constraint.get_max_height();
    bst.root = new BStarT_node(&block_hash[block_name[0]]);
    bst.root->block->coord.x = 0;
    bst.root->block->coord.y = 0;
    int curr_len = bst.root->block->len;
    BStarT_node *curr_head = bst.root;
    BStarT_node *curr_node = bst.root;
    BStarT_node *add_node;
    node_hash.insert(make_pair(curr_node->block->name,curr_node));

    for(auto key = block_name.begin()+1; key !=block_name.end(); key++)
    {
        add_node = new BStarT_node(&block_hash[*key]);
        node_hash.insert(make_pair(add_node->block->name,add_node));
        //block place: right
        if(curr_len + block_hash[*key].len <= max_width)
        {
            curr_node->degree += 1;
            curr_node->left_child = add_node;
            curr_node->left_child->parent = curr_node;
            curr_node->left_child->level = curr_node->level + 1;
            curr_node = curr_node->left_child;
            curr_len = curr_len + block_hash[*key].len;
        }
        //block place: up
        else
        {
            curr_len = 0;
            curr_node = curr_head;
            curr_node->degree += 1;
            curr_node->right_child = add_node;
            curr_node->right_child->parent = curr_node;
            curr_node->right_child->level = curr_node->level + 1;
            curr_node = curr_node ->right_child;
            curr_head = curr_head->right_child;
            curr_len = curr_len + block_hash[*key].len;
        }
    }
}

void BStarT::traverse(BStarT_node *curr_node)
{
    if (curr_node != NULL)
    {
        cout <<"level:"<<curr_node->level<<":"<< *(curr_node->block);
        traverse(curr_node->left_child);
        traverse(curr_node->right_child);
    }
}

void BStarT::block_rotate(string block_name)
{
    node_hash[block_name]->block->rotate();
}

void BStarT::block_swap(string block_name_1, string block_name_2)
{
    swap(node_hash[block_name_1]->block,node_hash[block_name_2]->block);
}

void BStarT::packing(Constraint &constraint)
{
    int max_width = constraint.get_max_width();
    int max_height = constraint.get_max_height();
    this->contour.clear();
    this->contour.resize(max_width*2,0);
    this->width = 0;
    this->height = 0;
    int curr_width = 0;
    int curr_height = 0;

    stack<BStarT_node*> stack;
    stack.push(this->root);
    while(!stack.empty())
    {
        BStarT_node* curr_node = stack.top();
        stack.pop();
        /***** node process *****/
        //update coordinate x
        if (curr_node == this->root)
        {
            curr_node -> block -> coord.x = 0;
        }
        else if (curr_node->parent->left_child == curr_node)
        {
            curr_node -> block -> coord.x = curr_node->parent->block->coord.x + curr_node->parent->block->len;
        }
        else if (curr_node->parent->right_child == curr_node)
        {
            curr_node -> block -> coord.x = curr_node->parent->block->coord.x;
        }
        // expand contour size
        if (curr_node->block->len + curr_node -> block -> coord.x > this->contour.size())
        {
            cout<<"expend!"<<endl;
            this->contour.resize(this->contour.size()*2);
        }
        //update contour
        for (int i = curr_node->block->coord.x; i < curr_node->block->len + curr_node -> block -> coord.x; i++)
        {
            this->contour[i] += curr_node->block->height;
        }
        auto max = max_element(begin(this->contour) + (curr_node->block->coord.x), begin(this->contour) + (curr_node->block->len + curr_node -> block -> coord.x));
        for (int i = curr_node->block->coord.x; i < curr_node->block->len + curr_node -> block -> coord.x; i++)
        {
            bst.contour[i] = *max;
        }
        //update coordinate y
        curr_node->block->coord.y = *max - curr_node->block->height;
        /***** DFS *****/
        if(curr_node->right_child != NULL)
        {
            stack.push(curr_node->right_child);
        }
        if(curr_node->left_child != NULL)
        {
            stack.push(curr_node->left_child);
        }
        else
        {
            if(curr_node->block->len + curr_node -> block -> coord.x > this->width)
            {
                this->width = curr_node->block->len + curr_node -> block -> coord.x;
            }
        }
    }
    this->height = *max_element(begin(this->contour), end(this->contour));
}

float BStarT::cost(float alpha, float beta)
{
    float R_star = this->height/this->width;
    float R = 1;
    float cost = alpha * this->area + beta * this->wirelength + (1 - alpha - beta) * (R_star - R) * (R_star - R);
    //cout<<this->height<<";"<<this->width;
    //cout<<"r:"<<R_star<<endl;
    return cost;
}

void BStarT::find_init_result(Constraint &constraint)
{
    srand(seed);
    int counter = 0;
    float best_height = 9999999;
    bool accept;
    bool op;
    string block1, block2;
    while(true)
    {
        op = rand()%2;
        if (op == 1)
        {
            block1 = block_name[rand()%block_name.size()];
            block2 = block_name[rand()%block_name.size()];
            while(block1 == block2)
            {
                block1 = block_name[rand()%block_name.size()];
                block2 = block_name[rand()%block_name.size()];
            }
            this->block_swap(block1, block2);
        }
        else if(op == 0)
        {
            block1 = block_name[rand()%block_name.size()];
            block2 = block1;
            this->block_rotate(block1);
        }

        this->packing(constraint);

        if(constraint.is_satisfy(this->width, this->height))
        {
            cout <<counter<<": seed:" <<seed<<endl;
            break;
        }
        //ignore
        if (best_height < this->height || this->width > constraint.get_max_width())
        {
            if (op == 1)
            {
                this->block_swap(block1, block2);
            }
            else if(op == 0)
            {
                this->block_rotate(block1);
            }
        }
        else if(best_height >= this->height && this->width <= constraint.get_max_width())
        {
            //cout <<"update: " <<"width: " <<this->width << "height: " <<this->height<<endl;
            best_height = this->height;
        }
        counter += 1;
    }
}

void BStarT::wirelen_cal()
{
    this->wirelength = 0;
    for(auto it = net_list.begin(); it != net_list.end(); it++)
    {
        this->wirelength += it->hpwl();
    }
}

void out_floorplan(char *filename, BStarT tree)
{
    ofstream out_file;
    out_file.open(filename, ios::out);
    out_file << "Wirelength "<< tree.wirelength<<endl;
    out_file << "Blocks"<<endl;
    for (auto it = block_name.begin();it != block_name.end();it++)
    {
        out_file<< block_hash[*it].name <<" "<<block_hash[*it].coord.x<<" "<<block_hash[*it].coord.y <<" "<<block_hash[*it].is_rotate<<endl;
    }
    out_file.close();
}

void BStarT::greedy_wirelen(Constraint &constraint, int time_limit)
{
    //1638676339
    srand(seed);
    int counter = 0;
    float best_cost = 999999;
    bool accept;
    bool op;
    string block1, block2;
    clock_t start, curr_time;
    start = clock();
    while(true)
    {
        op = rand()%2;
        if (op == 1)
        {
            block1 = block_name[rand()%block_name.size()];
            block2 = block_name[rand()%block_name.size()];
            while(block1 == block2)
            {
                block1 = block_name[rand()%block_name.size()];
                block2 = block_name[rand()%block_name.size()];
            }
            this->block_swap(block1, block2);
        }
        else if(op == 0)
        {
            block1 = block_name[rand()%block_name.size()];
            block2 = block1;
            this->block_rotate(block1);
        }

        this->packing(constraint);
        this->wirelen_cal();
        //ignore
        if (constraint.is_satisfy(this->width, this->height))
        {
            if(best_cost > this->cost(0,1))
            {
                //cout <<"update: " <<"width: " <<this->width << "height: " <<this->height<<"wirelen: "<<this->wirelength<<endl;
                best_cost = this->cost(0,1);
                //cout <<"best_cost:"<< best_cost<<"counter: "<<counter<<endl;
            }
            else
            {
                if (op == 1)
                {
                    this->block_swap(block1, block2);
                }
                else if(op == 0)
                {
                    this->block_rotate(block1);
                }
            }
        }
        else
        {
            if (op == 1)
            {
                this->block_swap(block1, block2);
            }
            else if(op == 0)
            {
                this->block_rotate(block1);
            }
        }
        curr_time = (double)(clock() - start)/CLOCKS_PER_SEC;
        if(curr_time >= time_limit)
        {
            cout <<" seed:" <<seed<<endl;
            break;
        }
        counter += 1;
        //cout<< counter<<endl;
    }
}

