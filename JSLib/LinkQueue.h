#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "Exception.h"
#include "Queue.h"
#include "LinuxList.h"

namespace JSLib
{

template < typename T>
class LinkQueue : public Queue<T>              //利用双向循环链表实现队列
{
protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };

    list_head m_header;
    int m_length;

public:
    LinkQueue()
    {
        m_length = 0;
        INIT_LIST_HEAD(&m_header);
    }

    void add(const T& e)
    {
        Node* node = new Node();
        if(node != NULL)
        {
            node->value = e;
            list_add_tail(&node->head,&m_header);
            m_length++;
        }
        else
        {
            THROWEXCEPTION(NoEnoughMemoryException,"No memory to creat LinkQueue's node");
        }
    }

    void remove()
    {
        if(m_length > 0)
        {
            list_head* toDel = m_header.next;
            list_del(toDel);
            m_length--;
            delete list_entry(toDel,Node,head);
        }
        else
        {
            THROWEXCEPTION(InvalidOperationException,"No element in current Queue");
        }
    }

    T front()const
    {
        if(m_length > 0)
        {
            return list_entry(m_header.next,Node,head)->value;
        }
        else
        {
            THROWEXCEPTION(InvalidOperationException,"No element in current Queue");
        }
    }

    void clear()
    {
        while(m_length > 0)
        {
            remove();
        }
    }

    int length() const
    {
        return m_length;
    }

    ~LinkQueue()
    {
        clear();
    }
};


}


#endif // LINKQUEUE_H
