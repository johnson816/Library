#ifndef BTREENODE_H
#define BTREENODE_H

#include "TreeNode.h"

namespace JSLib
{

/**
 **该枚举类型定义了执行二叉树插入操作时，节点的插入位置。
 **ANY表示待插入的节点可以插入在父节点的任意位置。
 **LEFT表示待插入的节点应该插入在父节点的左子树位置。
 **RIGHT表示待插入的节点应该插入在父节点的右子树位置
 **/
enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
};

template < typename T >
class BTreeNode : public TreeNode<T>
{
public:
    BTreeNode<T>* left;              //左子树
    BTreeNode<T>* right;             //右子树

    BTreeNode() : left(NULL),right(NULL)
    {

    }

    static BTreeNode<T>* NewNode()           //创建节点的工厂方法
    {
        BTreeNode<T>* ret = new BTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;
        }

        return ret;
    }


};

}

#endif // BTREENODE_H
