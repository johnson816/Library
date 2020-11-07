#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "Queue.h"
#include "Exception.h"

namespace JSLib
{

template < typename T ,int N>
class StaticQueue : public Queue<T>
{
protected:
    T m_space[N];                    //队列存储空间，N为模板参数
    int m_front;                     //队头标识
    int m_rear;                      //队尾标识
    int m_length;                    //当前队列长度
public:
    StaticQueue()
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }

    int capacity() const
    {
        return N;
    }

    void add(const T& e)
    {
        if(m_length < N)
        {
            m_space[m_rear] = e;
            m_rear = (m_rear + 1) % N;
            m_length++;
        }
        else
        {
            THROWEXCEPTION(InvalidOperationException,"No space in current Queue");
        }
    }

    void remove()
    {
        if(m_length > 0)
        {
            m_front = (m_front + 1) % N;
            m_length--;
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
            return m_space[m_front];
        }
        else
        {
            THROWEXCEPTION(InvalidOperationException,"No element in current Queue");
        }
    }

    void clear()
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }

    int length() const
    {
        return m_length;
    }
};


}

#endif // STATICQUEUE_H
