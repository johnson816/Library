#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"

namespace JSLib
{
template
<typename T>
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    mutable struct : public Object
    {
        char reserve[sizeof(T)];
        Node* next;
    }m_header;

    int m_length;
    Node* position(int i)  const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);
        for(int p=0;p<i;p++)
        {
            ret = ret->next;
        }
        return ret;
    }

public:
    LinkList()
    {
        m_header.next = NULL;
        m_length = 0;
    }

    bool insert(const T& obj)
    {
        return insert(m_length,obj);
    }

    bool insert(int i,const T& obj)
    {
        bool ret = ((0 <= i) && (i <= m_length));
        if(ret)
        {
            Node* tem = new Node();
            if(tem != NULL)
            {
                Node* current = position(i);
                tem->value = obj;
                tem->next = current->next;
                current->next = tem;
                m_length++;
            }
            else
            {
                THROWEXCEPTION(NoEnoughMemoryException,"No memory to creat Node");
            }

        }
        return ret;
    }

    bool remove(int i)
    {
        bool ret = ((0 <= i) && (i <m_length));
        if(ret)
        {
            Node* current = position(i);
            Node * toDel = current->next;
            current->next = toDel->next;
            delete toDel;
            m_length--;
        }
        else
        {
            THROWEXCEPTION(IndexOutOfBoundsException,"parameter i is invald");
        }
        return ret;
    }

    T get(int i) const
    {
        T ret ;
        if(get(i,ret))
        {
            return ret;
        }
        else
        {
            THROWEXCEPTION(IndexOutOfBoundsException,"Invalid parameter i to get()");
        }
        return ret;
    }

    bool get(int i,T& obj) const
    {
        bool ret = ((0 <= i) && (i <m_length));
        if(ret)
        {
            obj = position(i)->next->value;

        }
        else
        {
            THROWEXCEPTION(IndexOutOfBoundsException,"parameter i is invald");
        }
        return ret;
    }
    bool set(int i, const T& obj)
    {
        bool ret = ((0 <= i) && (i <m_length));
        if(ret)
        {
            position(i)->next->value = obj;
        }
        else
        {
            THROWEXCEPTION(IndexOutOfBoundsException,"parameter i is invald");
        }
        return ret;
    }

    int find(const T& e) const
    {
        int ret = -1;
        int i = 0;
        Node* pNode = m_header.next;
        while(pNode)
        {
            if(pNode->value == e)
            {
                ret = i;
                break;
            }
            else
            {
                pNode = pNode->next;
                i++;
            }
        }
        return ret;
    }

    int length() const
    {
        return m_length;
    }
    void clear()
    {
        while(m_header.next)
        {
            Node *toDel = m_header.next;
            m_header.next = toDel->next;
            delete toDel;
        }
        m_length = 0;
    }
    ~LinkList()
    {
        clear();
    }
};
}



#endif // LINKLIST_H
