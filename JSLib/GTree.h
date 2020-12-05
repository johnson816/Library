#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"

namespace JSLib
{

template < typename T>
class GTree : public Tree<T>
{
protected:
    LinkQueue< GTreeNode<T>* > m_queue;                     //利用队列实现树的层次遍历

    GTree(const GTree<T>&);
    GTree<T>& operator =(const GTree<T>&);

    /**
     **在树中从node节点开始查找，查找值为value的节点，并将该节点的地址返回
     **/
    GTreeNode<T>* find(GTreeNode<T>* node,const T& value) const
    {
        GTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(node->value == value)
            {
                return node;
            }
            else
            {
                for(node->child.move(0);!node->child.end()&& (ret==NULL);node->child.next())
                {
                    ret = find(node->child.current(),value);
                }
            }
        }

        return ret;
    }

   /**
    **在树中从node节点开始查找，查找obj节点，并将该节点的地址返回
    **/
    GTreeNode<T>* find(GTreeNode<T>* node,GTreeNode<T>* obj) const
    {
        GTreeNode<T>* ret = NULL;
        if(node == obj)
        {
            return node;
        }
        else
        {
            if(node != NULL)
            {
                for(node->child.move(0);!node->child.end() && (ret == NULL);node->child.next())
                {
                    ret = find(node->child.current(),obj);
                }
            }
        }

        return ret;
    }

    /**
     **清除以Node为根节点的树
     **/
    void free(GTreeNode<T>* Node)
    {
        if( Node != NULL )
        {
            for(Node->child.move(0);!Node->child.end();Node->child.next())
            {
                free(Node->child.current());
            }

            if( Node->flag() )                   //判断节点是否在堆空间中
            {
                delete Node;
            }

        }
    }

    /**
     **删除以Node节点为根节点的子树，然后将删除的子树存放到堆空间之后返回。
     **/
    void remove(GTreeNode<T>* Node,GTree<T>*& ret)
    {
        ret = new GTree<T>();
        if( ret != NULL )
        {
            if( this->m_root  == Node )
            {
                this->m_root = NULL;
            }
            else
            {
                LinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*>(Node->parent)->child;
                child.remove(child.find(Node));
                Node->parent = NULL;

            }

            ret->m_root = Node;
        }
        else
        {
            THROWEXCEPTION(NoEnoughMemoryException,"No Memory to creat new Tree");
        }
    }

    /**
     **计算以node为根节点的树的节点数目
     **/
    int count(GTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            ret = 1;

            for(node->child.move(0);!node->child.end();node->child.next())  //计算子树节点数目
            {
                ret += count(node->child.current());
            }
        }

        return ret;
    }

    /**
     **计算以node为根节点的树的高度
     **/
    int height(GTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            for(node->child.move(0);!node->child.end();node->child.next()) //计算子树的高度
            {
                int h = height(node->child.current());

                if( h > ret )                                          //找到子树中的最大高度
                {
                    ret = h;
                }
            };

            ret = ret + 1;
        }

        return ret;
    }

    /**
     **计算以node为根节点的树的度
     **/
    int degree(GTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            ret = node->child.length();

            for(node->child.move(0);!node->child.end();node->child.next())  //计算子树的度
            {
                int d = degree(node->child.current());

                if( ret < d )                                       //找出树中最大的度
                {
                    ret = d;
                }
            }
        }

        return ret;
    }

public:
    GTree()
    {

    }

    /**
     **在树中插入node结点
     **/
    bool insert(TreeNode<T>* node)
    {
        bool ret = true;

        if( node != NULL )
        {
            if(this->m_root == NULL)    //如果没有根节点，则将插入的节点作为根节点
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                GTreeNode<T>* pParent = find(node->parent);  //找到要插入的节点的父节点
                if(pParent != NULL)
                {
                    GTreeNode<T>* n = dynamic_cast< GTreeNode<T>* >(node);
                    if(pParent->child.find(n) < 0)   //判断父节点的子节点中是否已经存在待插入的节点
                    {
                        pParent->child.insert(n);
                    }
                }
                else
                {
                    THROWEXCEPTION(InvalidOperationException,"Invalid parent tree node");
                }
            }
        }
        else
        {
            THROWEXCEPTION(InvalidParameterException,"parameter node cannot be NULL");
        }

        return ret;
    }


    /**
     **在树中插入值为value的节点，其父节点为parent
     **/
    bool insert(const T& value,TreeNode<T>* parent)
    {
        bool ret = true;
        GTreeNode<T>* Node =  GTreeNode<T>::NewNode();

        if(Node != NULL)
        {
            Node->value = value;
            Node->parent = parent;
            insert(Node);
        }
        else
        {
            THROWEXCEPTION(NoEnoughMemoryException,"No memory to creat tree node");
        }

        return ret;
    }

    /**
     **删除值为value为根节点的子树，并将其地址用智能指针返回
     **/
    SharedPointer< Tree<T> > remove(const T& value)
    {
        GTree<T>* ret = NULL;
        GTreeNode<T>* node = find(value);        //找到待删除的节点

        if(node != NULL)
        {
            remove(node,ret);
            m_queue.clear();
        }
        else
        {
            THROWEXCEPTION(InvalidParameterException,"Can no find node via this value");
        }

        return ret;

    }

    /**
     **删除node为根节点的子树，并将其地址用智能指针返回
     **/
    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        GTree<T>* ret = NULL;
        node = find(node);

        if(node != NULL)
        {
            remove(dynamic_cast<GTreeNode<T>*>(node),ret);
            m_queue.clear();
        }
        else
        {
            THROWEXCEPTION(InvalidParameterException,"Parameter node is invalid");
        }

        return ret;
    }

    /**
     **查找值为value的节点
     **/
    GTreeNode<T>* find(const T& value) const
    {
        return find(root(),value);
    }

    /**
     **在树中查找node节点
     **/
    GTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(),dynamic_cast< GTreeNode<T>* >(node));
    }

    /**
     **返回指向根节点的指针
     **/
    GTreeNode<T>* root()const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }

    /**
     **计算树的度
     **/
    int degree() const
    {
        return degree(root());
    }

    /**
     **计算树的节点数目
     **/
    int count() const
    {
        return count(root());
    }

    /**
     **计算树的高度
     **/
    int height() const
    {
        return height(root());
    }

    /**
     **清空树
     **/
    void clear()
    {
        free(root());
        this->m_root = NULL;
        m_queue.clear();
    }

    /**
     **以下begin，end，next，current函数用来实现树的层次遍历
     **begin 实现将树的根节点插入队列中
     **end 判断队列是否为空
     **next 将队列的头部元素弹出，并将头部元素的子树插入队列
     **current 实现将队列的头部元素中节点的值返回
     **/
    bool begin()
    {
        bool ret = (root() != NULL);

        if( ret )
        {
            m_queue.clear();
            m_queue.add(root());
        }

        return ret;
    }

    bool end()
    {
        return (0 == m_queue.length());
    }

    bool next()
    {
        bool ret = (m_queue.length() > 0);

        if( ret )
        {
            GTreeNode<T>* node = m_queue.front();

            m_queue.remove();

            for(node->child.move(0);!node->child.end();node->child.next())
            {
                m_queue.add(node->child.current());
            }
        }

        return ret;
    }

    T current()
    {
        bool ret = (!end());

        if( ret )
        {
            return m_queue.front()->value;
        }
        else
        {
            THROWEXCEPTION(InvalidOperationException,"No value in this position");
        }


    }

    ~GTree()
    {
        clear();
    }
};

}

#endif // GTREE_H
