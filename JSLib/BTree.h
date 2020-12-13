#ifndef BTREE_H
#define BTREE_H


#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"
#include "DynamicArray.h"

namespace JSLib
{


/**
 **该枚举类型定义了二叉树的其他典型遍历方式。
 **PreOrder表示先序遍历。
 **InOrder表示中序遍历。
 **PostOrder表示后序遍历
 **LevelOrder表示层次遍历
 **/
enum BTTraversal
{
    PreOrder,
    InOrder,
    PostOrder,
    LevelOrder
};

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

    /**
     **二叉树先序遍历
     **/
    void preOrderTraversal(BTreeNode<T>* node,LinkQueue< BTreeNode<T>* >& queue)
    {
        if( node != NULL )
        {
            queue.add(node);
            preOrderTraversal(node->left,queue);
            preOrderTraversal(node->right,queue);
        }
    }

    /**
     **二叉树中序遍历
     **/
    void inOrderTraversal(BTreeNode<T>* node,LinkQueue< BTreeNode<T>* >& queue)
    {
        if( node != NULL )
        {
            inOrderTraversal(node->left,queue);
            queue.add(node);
            inOrderTraversal(node->right,queue);
        }
    }

    /**
     **二叉树后序遍历
     **/
    void postOrderTraversal(BTreeNode<T>* node,LinkQueue< BTreeNode<T>* >& queue)
    {
        if( node != NULL )
        {
            postOrderTraversal(node->left,queue);
            postOrderTraversal(node->right,queue);
            queue.add(node);
        }
    }

    /**
     **二叉树层次遍历，把遍历之后的节点有序的放入队queue中
     **/
    void leverOrderTraversal(BTreeNode<T>* node,LinkQueue< BTreeNode<T>* >& queue)
    {
        if( node != NULL )
        {
            LinkQueue<BTreeNode<T>*> tem;

            tem.add(node);

            while( tem.length() > 0 )
            {
                BTreeNode<T>* n = tem.front();

                if( n->left != NULL )
                {
                    tem.add(n->left);
                }

                if( n->right != NULL )
                {
                    tem.add(n->right);
                }

                tem.remove();
                queue.add(n);
            }

        }
    }

    /**
     **拷贝以node节点为根节点的二叉树
     **/
    BTreeNode<T>* clone(BTreeNode<T>* node) const
    {
        BTreeNode<T>* ret = BTreeNode<T>::NewNode();

        if( ret != NULL )
        {
            if( node != NULL )
            {
                ret->value = node->value;
                ret->left = clone(node->left);
                ret->right = clone(node->right);

                if( ret->left != NULL )
                {
                    ret->left->parent = ret;
                }

                if( ret->right != NULL )
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                ret = NULL;
            }
        }
        else
        {
            THROWEXCEPTION(NoEnoughMemoryException,"No memory to creat BTreeNode");
        }

        return ret;


    }

    /**
     **判断lh为根节点的二叉树和rh为根节点的二叉树是否相等
     **/
    bool equal(BTreeNode<T>* lh,BTreeNode<T>* rh)
    {
        if( lh == rh )
        {
            return true;
        }
        else if( (lh != NULL ) && (rh != NULL ) )
        {
            return ((lh->value == rh->value) && (equal(lh->left,rh->left)) && (equal(lh->right,rh->right)));
        }
        else
        {
            return false;
        }
    }

    /**
     **将lh为根节点的二叉树和rh为根节点的二叉树相加，返回相加后的二叉树
     **/
    BTreeNode<T>* add(BTreeNode<T>* lh,BTreeNode<T>* rh) const
    {
        BTreeNode<T>* ret = NULL;

        if( (lh != NULL) && (rh == NULL) )
        {
            ret = clone(lh);
        }
        else if( (lh == NULL) && (rh != NULL) )
        {
            ret = clone(rh);
        }
        else if( (lh != NULL) && (rh != NULL))
        {
            ret = BTreeNode<T>::NewNode();

            if( ret != NULL )
            {
                ret->value = lh->value + rh->value;
                ret->left = add(lh->left,rh->left);
                ret->right = add(lh->right,rh->right);

                if( ret->left != NULL )
                {
                    ret->left->parent = ret;
                }

                if( ret->right != NULL )
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROWEXCEPTION(NoEnoughMemoryException,"No memory to creat BTreeNode");
            }

        }

        return ret;
    }

    /**
     **遍历功能函数，遍历方式为order，遍历后的节点放入queue中
     **/
    void traversal(BTTraversal order,LinkQueue<BTreeNode<T>*>& queue)
    {
        switch(order)
        {
        case PreOrder:
            preOrderTraversal(root(),queue);
            break;
        case InOrder:
            inOrderTraversal(root(),queue);
            break;
        case PostOrder:
            postOrderTraversal(root(),queue);
            break;
        case LevelOrder:
            leverOrderTraversal(root(),queue);
            break;
        default:
            THROWEXCEPTION(InvalidParameterException,"Parameter order is invalid");
            break;
        }
    }

    /**
     **将队列queue中的二叉树节点链接成双向链表，返回指向双向链表头节点的指针
     **/
    BTreeNode<T>* connet(LinkQueue<BTreeNode<T>*>& queue)
    {
        BTreeNode<T>* ret = NULL;

        if( queue.length() > 0 )
        {
            ret = queue.front();

            BTreeNode<T>* slide = queue.front();
            queue.remove();
            slide->left = NULL;

            while( queue.length() > 0 )
            {
                slide->right = queue.front();
                queue.front()->left = slide;
                slide = queue.front();
                queue.remove();
            }

            slide->right = NULL;
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

    SharedPointer< Array<T> > traversal(BTTraversal order)
    {
        DynamicArray<T>* ret = NULL;
        LinkQueue< BTreeNode<T>* > queue;

        traversal(order,queue);

        ret = new DynamicArray<T>(queue.length());

        if( ret != NULL )
        {
            for(int i=0;i<ret->length();i++,queue.remove())
            {
                ret->set(i,queue.front()->value);
            }
        }
        else
        {
            THROWEXCEPTION(NoEnoughMemoryException,"No memory to creat return array");
        }

        return ret;

    }

    SharedPointer< BTree<T> > clone()const
    {
        BTree<T>* ret = new BTree<T>();

        if( ret != NULL )
        {
            ret->m_root = clone(root());
        }
        else
        {
            THROWEXCEPTION(NoEnoughMemoryException,"No memory to creat BTree Node");
        }

        return ret;
    }

    bool operator == (const BTree<T>& btree)
    {
        return (equal(root(),btree.root()));
    }

    bool operator != (const BTree<T>& btree)
    {
        return !(*this == btree);
    }

    SharedPointer< BTree<T> > add(const BTree<T>& btree) const
    {
        BTree<T>* ret = new BTree<T>();

        if( ret != NULL )
        {
            ret->m_root= add(root(),btree.root());
        }
        else
        {
            THROWEXCEPTION(NoEnoughMemoryException,"No memory to creat BTree");
        }

        return ret;
    }

    /**
     **将二叉树线索化函数，返回指向双向链表头节点的指针
     **/
    BTreeNode<T>* thread(BTTraversal order)
    {
        BTreeNode<T>* ret = NULL;
        LinkQueue<BTreeNode<T>*> queue;

        traversal(order,queue);

        ret = connet(queue);

        this->m_root = NULL;
        queue.clear();

        return ret;
    }

    ~BTree()
    {
        clear();
    }
};

}
#endif // BTREE_H
