#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace JSLib
{

template < typename T >
class TreeNode : public Object
{
protected:
    bool m_flag;                                    //标志节点是否是在堆空间创建的，true标识该节点在堆空间创建

    TreeNode(const TreeNode<T>&);
    TreeNode<T>& operator =(const TreeNode<T>&);

    void* operator new(unsigned int size) throw()
    {
        return Object::operator new(size);
    }
public:
    T value;                           //存储的数据
    TreeNode<T>* parent;               //指向父结点指针

    TreeNode() : m_flag(false),parent(NULL)
    {

    }

    bool flag()
    {
        return m_flag;
    }

    virtual ~TreeNode() = 0;
};

template < typename T >
TreeNode<T>::~TreeNode()
{

}

}



#endif // TREENODE_H
