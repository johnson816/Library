#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "Stack.h"
#include "LinkList.h"

namespace JSLib
{

template < typename T>
class LinkStack : public Stack<T>
{
protected:
    LinkList<T>m_list;

public:
    void push(const T& e)
    {
        m_list.insert(0,e);
    }

    void pop()
    {
        if(m_list.length() > 0)
        {
            m_list.remove(0);
        }
        else
        {
            THROWEXCEPTION(InvalidParameterException,"No element in current Stack");
        }

    }

    T top() const
    {
        if(m_list.length() > 0)
        {
            return m_list.get(0);
        }
        else
        {
            THROWEXCEPTION(InvalidParameterException,"No element in current Stack");
        }

    }

    void clear()
    {
        m_list.clear();
    }

    int size() const
    {
        return m_list.length();
    }

};

}


#endif // LINKSTACK_H
