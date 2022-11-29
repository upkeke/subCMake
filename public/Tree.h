#ifndef _TREE_
#define _TREE_
#include"head.h"
template<typename T>
class Tree
{
    T val;
    Tree* left;
    Tree* right;
public:
    Tree(T val,Tree*left,Tree*right):
    val(val),left(left),right(right){}

    T get_val()
    {
        return val;
    }
};

void HelloTree();



#endif