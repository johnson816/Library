#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace JSLib
{

template < typename T,int N>
class StaticStack : public Stack<T>
{
protected:
    T m_space[N];                   //栈存储空间，N为模板参数
    int m_top;                      //栈顶标识
    int m_size;                     //当前栈的大小

public:
    StaticStack()
    {
        m_top = -1;
        m_size = 0;
    }

    int capacity() const
    {
        return N;
    }

    void push(const T& e)
    {
        if(m_size < N)
        {
            m_space[m_top + 1] = e;
            m_top++;
            m_size++;
        }
        else
        {
            THROWEXCEPTION(InvalidParameterException,"No space int current Stack");
        }
    }

    void pop()
    {
        if(m_size > 0)
        {
            m_top--;
            m_size--;
        }
        else
        {
            THROWEXCEPTION(InvalidParameterException,"No element int current Stack");
        }
    }

    T top() const
    {
        if(m_size > 0)
        {
            return m_space[m_top];
        }
        else
        {
            THROWEXCEPTION(InvalidParameterException,"No element int current Stack");
        }
    }

    void clear()
    {
        m_top = -1;
        m_size = 0;
    }

    int size() const
    {
        return m_size;
    }

    ~StaticStack()
    {
        clear();
    }

};

}

#endif // STATICSTACK_H
