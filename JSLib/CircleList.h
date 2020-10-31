#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "LinkList.h"

namespace JSLib
{

template < typename T >
class CircleList : public LinkList<T>
{

protected:
    typedef typename LinkList<T>::Node Node;

    Node* last() const                                     // 返回指向尾节点的指针
    {
        return (this->position(this->m_length -1)->next);
    }

    void last_to_first()                                   //连接单链表的尾节点和头节点
    {
        last()->next = this->m_header.next;
    }

    int mod(int i) const                                       //将i归一化处理
    {
        return (this->m_length == 0) ? 0 : (i % this->m_length);
    }

public:
    bool insert(const T& obj)
    {
        return (insert(this->m_length,obj));
    }

    bool insert(int i, const T& obj)
    {
        bool ret = true;
        i = i%(this->m_length + 1);                         //循环链表，i可能会很大，将i归一化处理
        ret = LinkList<T>::insert(i,obj);
        if(ret && (i == 0))
        {
            last_to_first();
        }
        return ret;
    }
    bool remove(int i)
    {
        bool ret = true;
        i = mod(i);
        if(i == 0)
        {
            Node* toDel = this->m_header.next;
            if(toDel != NULL)
            {
                this->m_header.next = toDel->next;
                this->m_length--;
                if(this->m_length == 0)
                {
                    this->m_header.next = NULL;
                    this->m_current = NULL;
                }
                else
                {
                    last_to_first();
                    if(this->m_current == toDel)
                    {
                        this->m_current = toDel->next;
                    }
                }
                this->destroy(toDel);
            }
            else
            {

                ret = false;
            }

        }
        else
        {
            ret = LinkList<T>::remove(i);
        }

        return ret;

    }

    bool set(int i, const T& obj)
    {
        return LinkList<T>::set(mod(i),obj);
    }

    bool get(int i, T &obj) const
    {
        return LinkList<T>::get(mod(i),obj);
    }

    T get(int i) const
    {
        return (LinkList<T>::get(mod(i)));
    }

    int find(const T& obj) const
    {
        int ret = -1;
        Node* pTem = this->m_header.next;
        for(int i=0;i<this->m_length;i++)
        {
            if(pTem->value == obj)
            {
                ret = i;
                 break;
            }
            pTem = pTem->next;
        }
        return ret;
    }

    void clear()
    {
        while(this->m_length > 1)
        {
            remove(1);
        }
        if(this->m_length == 1)
        {
            Node* toDel = this->m_header.next;
            this->m_header.next = NULL;
            this->m_current = NULL;
            this->m_length = 0;
            this->destroy(toDel);
        }
    }

    bool move(int i, int step = 1)
    {
        return LinkList<T>::move(mod(i),step);
    }

    bool end()
    {
        return (this->m_current == NULL) || (this->m_length == 0) ;
    }

    ~CircleList()
    {
        clear();
    }

};

}

#endif // CIRCLELIST_H
