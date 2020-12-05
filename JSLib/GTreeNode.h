#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "LinkList.h"

namespace JSLib
{

template < typename T >
class GTreeNode : public TreeNode<T>
{
protected:
    bool m_flag;                                    //标志节点是否是在堆空间创建的，true标识该节点在堆空间创建

    GTreeNode(const GTreeNode<T>&);
    GTreeNode<T>& operator =(const GTreeNode<T>&);

    void* operator new(unsigned int size) throw()
    {
        return Object::operator new(size);
    }

public:
    LinkList< GTreeNode<T>* > child;   //存放指向子节点指针的链表

    GTreeNode() : m_flag(false)
    {

    }

    bool flag()
    {
        return m_flag;
    }

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
