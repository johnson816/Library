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
    Node* m_current;
    int m_step;

    Node* position(int i)  const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);
        for(int p=0;p<i;p++)
        {
            ret = ret->next;
        }
        return ret;
    }

    virtual Node* creat()
    {
        return new Node();
    }

    virtual void destroy(Node* pn)
    {
        delete pn;
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
            Node* tem = creat();
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
            if(m_current == toDel)
            {
                m_current = toDel->next;
            }
            current->next = toDel->next;
            m_length--;
            destroy(toDel);           
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

    bool move(int i,int step = 1)
    {
        bool ret = (0 <= i) && (i < m_length) && (step > 0);
        if(ret)
        {
            m_current = position(i)->next;
            m_step = step;
        }
        return ret;
    }

    bool end()
    {
        return(m_current == NULL);
    }

    T current()
    {
        if(!end())
        {
            return m_current->value;
        }
        else
        {
            THROWEXCEPTION(InvalidParameterException,"No value at current position");
        }
    }

    bool next()
    {
        int i =0;
        while((i < m_step) && (!end()))
        {
            m_current = m_current->next;
            i++;
        }
        return (i == m_step);
    }

    void clear()
    {
        while(m_header.next)
        {
            Node *toDel = m_header.next;
            m_header.next = toDel->next;
            m_length--;
            destroy(toDel);
        }  
    }
    ~LinkList()
    {
        clear();
    }
};
}



#endif // LINKLIST_H
