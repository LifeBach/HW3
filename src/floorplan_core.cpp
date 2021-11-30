#include "headers.h"
#include "parser.h"
#include "floorplan_core.h"

/*****************************************************************************
*   Global variable: declaration
*****************************************************************************/

BStarT bst;

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
    bst.contour.resize(max_width,0);
    bst.root = new BStarT_node(&block_hash[block_name[0]]);
    bst.root->block->coord.x = 0;
    bst.root->block->coord.y = 0;
    int curr_len = bst.root->block->len;
    int curr_height = bst.root->block->height;
    // update contour
    for (int i = 0; i<curr_len; i++)
    {
        bst.contour[i] += curr_height;
    }
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
            add_node->block->coord.x = curr_len;
            curr_node->degree += 1;
            curr_node->left_child = add_node;
            curr_node->left_child->parent = curr_node;
            curr_node->left_child->level = curr_node->level + 1;
            curr_node = curr_node->left_child;
            curr_len = curr_len + block_hash[*key].len;
            // update contour
            for (int i = curr_len -  block_hash[*key].len; i < curr_len; i++)
            {
                bst.contour[i] += add_node->block->height;
            }
            auto max = max_element(begin(bst.contour) + (curr_len -  block_hash[*key].len), begin(bst.contour) + curr_len);
            for (int i = curr_len -  block_hash[*key].len; i < curr_len; i++)
            {
                bst.contour[i] = *max;
            }
            add_node->block->coord.y = *max - add_node->block->height;
        }
        //block place: up
        else
        {
            curr_len = 0;
            add_node->block->coord.x = curr_len;
            curr_node = curr_head;
            curr_node->degree += 1;
            curr_node->right_child = add_node;
            curr_node->right_child->parent = curr_node;
            curr_node->right_child->level = curr_node->level + 1;
            curr_node = curr_node ->right_child;
            curr_head = curr_head->right_child;
            curr_len = curr_len + block_hash[*key].len;
            for (int i = curr_len -  block_hash[*key].len; i < curr_len; i++)
            {
                bst.contour[i] += add_node->block->height;
            }
            auto max = max_element(begin(bst.contour) + (curr_len -  block_hash[*key].len), begin(bst.contour) + curr_len);
            for (int i = curr_len -  block_hash[*key].len; i < curr_len; i++)
            {
                bst.contour[i] = *max;
            }
            add_node->block->coord.y = *max - add_node->block->height;
            
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

BStarT_node* BStarT::find(BStarT_node *curr_node, string name)
{
    if(curr_node != NULL)
    {
        if(curr_node->block->name == name)
        {
            return curr_node;
        }
        BStarT_node* left_node = find(curr_node->left_child, name);
        if(left_node->block->name == name) return left_node;
        BStarT_node* right_node = find(curr_node->right_child, name);
        if(right_node->block->name == name) return right_node;
    }
    return curr_node;
}

void BStarT::block_rotate(string block_name)
{
    node_hash[block_name]->block->rotate();
}

void BStarT::block_swap(string block_name_1, string block_name_2)
{
    swap(node_hash[block_name_1]->block,node_hash[block_name_2]->block);
}

void BStarT::update_contour(BStarT_node *curr_node, Constraint &constraint, int x)
{
    //base case
    if (curr_node == NULL) return;
    int max_width = constraint.get_max_width();
    int max_height = constraint.get_max_height();
    for (int i = x; i < x + curr_node->block->len; i++)
    {

    }
}