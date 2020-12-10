#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "LinkList.h"

namespace JSLib
{

template < typename T >
class GTreeNode : public TreeNode<T>
{
public:
    LinkList< GTreeNode<T>* > child;   //存放指向子节点指针的链表

    static GTreeNode<T>* NewNode()           //创建节点的工厂方法
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;
        }

        return ret;
    }

};

}


#endif // GTREENODE_H
