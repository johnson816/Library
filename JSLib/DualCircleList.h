#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H

#include "DualLinkList.h"
#include "LinuxList.h"

namespace JSLib
{

template < typename T >
class DualCircleList : public DualLinkList<T>
{

protected:
    struct Node : public Object
    {
        struct list_head head;
        T value;
    };

    list_head m_header;
    list_head* m_current;

    list_head* position(int i) const
    {
        list_head* ret = const_cast<list_head*>(&m_header);

        for(int p=0;p<i;p++)
        {
            ret = ret->next;
        }

        return ret;
    }

    int mod(int i) const
    {
        return (this->m_length == 0) ? 0 : (i % this->m_length);
    }

public:
    DualCircleList()
    {
        this->m_length = 0;
        this->m_step = 1;

        this->m_current = NULL;
        INIT_LIST_HEAD(&m_header);
    }

    bool insert(const T& obj)
    {
        return insert(this->m_length,obj);
    }

    bool insert(int i,const T& obj)
    {
        bool ret = true;
        Node* node = new Node();

        i = i % (this->m_length + 1);

        if(node != NULL)
        {
            node->value = obj;

            list_add_tail(&node->head,position(i)->next);

            this->m_length++;
        }
        else
        {
            THROWEXCEPTION(NoEnoughMemoryException,"No enough memory to creat node");
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = true;

        i = mod(i);
        ret = (ret) && (0 <= i) && (i < this->m_length);

        if(ret)
        {
            list_head* toDel = position(i)->next;
            if(this->m_current == toDel)
            {
                m_current = m_current->next;
            }

            list_del(toDel);
            this->m_length--;

            delete list_entry(toDel,Node,head);
        }
        return ret;
    }

    virtual T get(int i) const
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
        bool ret = true;
        i = mod(i);
        ret = ((0 <= i) && (i <this->m_length));
        if(ret)
        {
            obj = list_entry(position(i)->next,Node,head)->value;

        }
        else
        {
            THROWEXCEPTION(IndexOutOfBoundsException,"parameter i is invald");
        }
        return ret;
    }
    bool set(int i, const T& obj)
    {
        bool ret = true;
        i = mod(i);
        ret = ((0 <= i) && (i < this->m_length));

        if(ret)
        {
            list_entry(position(i)->next,Node,head)->value = obj;
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
        list_head* slider = NULL;
        int i=0;

        list_for_each(slider, &m_header)
        {
            if(list_entry(slider,Node,head)->value == e)
            {
                ret = i;
                break;
            }

            slider = slider->next;
        }
        return ret;
    }

    int length() const
    {
        return this->m_length;
    }

    void clear()
    {
        while(this->m_length > 0)
        {
            remove(0);
        }
    }

    bool move(int i,int step = 1)
    {
        bool ret = (step > 0);
        i = mod(i);
        ret = ret && ((0 <= i) && (i < this->m_length));

        if(ret)
        {
            this->m_current = position(i)->next;
            this->m_step = step;
        }
        return ret;
    }

    bool end()
    {
        return (m_current == NULL) || (this->m_length == 0);
    }

    virtual T current()
    {
        if(!end())
        {
            return list_entry(m_current,Node,head)->value;
        }
        else
        {
            THROWEXCEPTION(InvalidParameterException,"No value at current position");
        }
    }

    bool next()
    {
        int i =0;
        while((i < this->m_step) && (!end()))
        {
            if(this->m_current == &m_header)
            {
                m_current = m_current->next;
            }
            else
            {
                m_current = m_current->next;
                i++;
            }
        }

        if(this->m_current == &m_header)
        {
            m_current = m_current->next;
        }

        return (i == this->m_step);
    }

    bool pre()
    {
        int i =0;

        while((i < this->m_step) && (!end()))
        {
            if(this->m_current == &m_header)
            {
                m_current = m_current->prev;
            }
            else
            {
                m_current = m_current->prev;
                i++;
            }
        }

        if(this->m_current == &m_header)
        {
            m_current = m_current->prev;
        }

        return (i == this->m_step);
    }

    ~DualCircleList()
    {
        clear();
    }
};

}

#endif // DUALCIRCLELIST_H
