#ifndef BTREE_H
#define BTREE_H


#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"


namespace JSLib
{

template < typename T>
class BTree : public Tree<T>
{
protected:
    LinkQueue<BTreeNode<T>*>m_queue;     //利用队列实现二叉树的层次遍历

    /**
     **在树中从node节点开始查找，查找值为value的节点，并将该节点的地址返回
     **/
    virtual BTreeNode<T>* find(BTreeNode<T>* node,const T& value) const
    {
        BTreeNode<T>* ret = NULL;
        if( node != NULL )
        {
            if( node->value == value )
            {
                ret = node;
            }
            else
            {
                if( NULL == ret )
                {
                    ret = find(node->left,value);
                }

                if( NULL == ret )
                {
                    ret = find(node->right,value);
                }

            }

        }
        return ret;
    }

    /**
     **在树中从node节点开始查找，查找obj节点，并将该节点的地址返回
     **/
    virtual BTreeNode<T>* find(BTreeNode<T>* node,BTreeNode<T>* obj) const
    {
        BTreeNode<T>* ret = NULL;

        if( node == obj )
        {
            ret = node;
        }
        else
        {
            if( node != NULL )
            {
                if( NULL == ret )
                {
                    ret = find(node->left,obj);
                }

                if( NULL == ret )
                {
                    ret = find(node->right,obj);
                }
            }
        }

        return ret;
    }

    /**
     **在树中插入节点n，其父节点为np,插入的位置为pos
     **/
    virtual bool insert(BTreeNode<T>* n,BTreeNode<T>* np,BTNodePos pos)
    {
        bool ret = true;

        if( pos == ANY )
        {
            if( np->left == NULL )
            {
                np->left = n;
            }

            else if( np->right == NULL )
            {
                np->right = n;
            }
            else
            {
                ret = false;
            }
        }
        else if( pos == LEFT )
        {
            if( np->left == NULL )
            {
                np->left = n;
            }
            else
            {
                ret = false;
            }
        }
        else if( pos == RIGHT )
        {
            if( np->right == NULL )
            {
                np->right = n;
            }
            else
            {
                ret = false;
            }
        }

        return ret;
    }

    /**
     **删除以Node节点为根节点的子树，然后将删除的子树存放到堆空间之后返回。
     **/
    virtual void remove(BTreeNode<T>* node,BTree<T>*& ret)
    {
        ret = new BTree();

        if( ret != NULL )
        {
            if( node == root() )
            {
                this->m_root = NULL;
            }
            else
            {
                BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);

                if( parent->left == node)
                {
                    parent->left = NULL;
                }
                else if( parent->right == node )
                {
                    parent->right = NULL;
                }

                node->parent = NULL;
            }
        }
        else
        {
            THROWEXCEPTION(NoEnoughMemoryException,"No memroy to creat BTree");
        }

        ret->m_root = node;
    }

    /**
     **清除以Node为根节点的树
     **/
    virtual void free(BTreeNode<T>* node)
    {
        if( node != NULL )
        {
            free(node->left);
            free(node->right);

            if( node->flag() )
            {
                delete node;
            }
        }
    }

    /**
     **计算以node为根节点的树的节点数目
     **/
    int count(BTreeNode<T>* node) const
    {
        return (node != NULL) ? (count(node->left) + count(node->right) + 1) : 0;
    }

    /**
     **计算以node为根节点的树的高度
     **/
    int height(BTreeNode<T>* node) const
    {
        int ret = 0;

        if( node != NULL )
        {
            int lh = height(node->left);
            int rh = height(node->right);

            ret = (lh > rh) ? (lh + 1) : (rh + 1);
        }

        return ret;
    }

    /**
     **计算以node为根节点的树的度
     **/
    int degree(BTreeNode<T>* node) const
    {
        int ret = 0;
        BTreeNode<T>* buf[2] = { node->left,node->right };
        ret = !!node->left + !!node->right;

        for(int i=0;(i<2) && (ret<2);i++)
        {
            int d = degree(buf[i]);

            if(ret < d)
            {
                ret = d;
            }
        }

        return ret;

    }

public:
    /**
     **在树中插入node结点，插入的位置任意
     **/
    bool insert(TreeNode<T>* node)
    {
        return insert(node,ANY);
    }

    /**
     **在树中插入node结点，插入的位置在其父节点的pos位置
     **/
    virtual bool insert(TreeNode<T>* node,BTNodePos pos)
    {
        bool ret = true;

        if( node != NULL)
        {
            if( this->m_root == NULL )
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                BTreeNode<T>* np = find(node->parent);     //找到待插入节点的父节点

                if( np != NULL )
                {
                    ret = insert(dynamic_cast<BTreeNode<T>*>(node),np,pos);
                }
                else
                {
                    THROWEXCEPTION(InvalidParameterException,"Invalid parent BTree node");
                }
            }

        }
        else
        {
            THROWEXCEPTION(InvalidParameterException,"Parameter node can no be NULL");
        }

        return ret;
    }

    /**
     **在树中插入node结点，其父节点为parent，插入的位置任意
     **/
    bool insert(const T& value,TreeNode<T>* parent)
    {
        return insert(value,parent,ANY);
    }

    /**
     **在树中插入node结点，其父节点为parent，插入的位置为pos
     **/
    virtual bool insert(const T& value,TreeNode<T>* parent,BTNodePos pos)
    {
        bool ret = true;
        BTreeNode<T>* node = BTreeNode<T>::NewNode();

        if( node != NULL )
        {
            node->value = value;
            node->parent = parent;

            ret = insert(node,pos);

            if( false == ret )     //插入失败
            {
                delete node;
            }
        }
        else
        {
            THROWEXCEPTION(NoEnoughMemoryException,"No memory to creat BTree node");
        }

        return ret;
    }

    /**
     **删除值为value为根节点的子树，并将其地址用智能指针返回
     **/
    SharedPointer< Tree<T> > remove(const T& value)
    { 
        BTree<T>* ret = NULL;
        BTreeNode<T>* node = find(value);

        if( node != NULL )
        {
            remove(node,ret);
            m_queue.clear();
        }
        else
        {
            THROWEXCEPTION(InvalidParameterException,"Can not find BTree node via value");
        }
        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        BTree<T>* ret = NULL;
        node = find(node);

        if( node != NULL )
        {
            remove(dynamic_cast<BTreeNode<T>*>(node),ret);
            m_queue.clear();
        }
        else
        {
            THROWEXCEPTION(InvalidParameterException,"Paramete node is invalid");
        }

        return ret;
    }

    /**
     **查找值为value的节点
     **/
    BTreeNode<T>* find(const T& value) const
    {
        return find(root(),value);
    }

    /**
     **在树中查找node节点
     **/
    BTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(),dynamic_cast< BTreeNode<T>* >(node));
    }

    /**
     **返回指向根节点的指针
     **/
    BTreeNode<T>* root()const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
    }

    int degree() const
    {
        return degree(root());
    }

    int count() const
    {
        return count((root()));
    }

    int height() const
    {
        return height(root());
    }

    void clear()
    {
        free(root());
        m_queue.clear();
        this->m_root = NULL;
    }

    /**
     **以下begin，end，next，current函数用来实现二叉树的层次遍历
     **begin 实现将二叉树的根节点插入队列中
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
            BTreeNode<T>* node = m_queue.front();

            m_queue.remove();

            if( node->left != NULL )
            {
                m_queue.add(node->left);
            }

            if( node->right != NULL )
            {
                m_queue.add(node->right);
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

    ~BTree()
    {
        clear();
    }
};

}
#endif // BTREE_H
