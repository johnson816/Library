#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace JSLib
{

template < typename T >
class TreeNode : public Object
{
public:
    T value;                           //存储的数据
    TreeNode<T>* parent;               //指向父结点指针

    TreeNode()
    {
        parent = NULL;
    }

    virtual ~TreeNode() = 0;
};

template < typename T >
TreeNode<T>::~TreeNode()
{

}

}



#endif // TREENODE_H
