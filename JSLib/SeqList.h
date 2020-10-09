#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception.h"

namespace JSLib
{

template <typename T>
class SeqList : public List<T>
{
protected:
    T* m_array;          //顺序存储空间
    int m_length;         //线性表长度
public:
    bool insert(int i,const T& obj)
    {
        bool ret = ((0 <= i) && (i <=m_length));
        ret = (ret) && (m_length < capacity());
        if(ret)
        {
            for(int p=m_length-1;p>=i;p--)
            {
                m_array[p + 1] = m_array[p];
            }
            m_array[i] = obj;
            m_length++;
        }
        return ret;
    }

    bool remove(int i)
    {
        bool ret = ((0 <= i) && (i < m_length));
        if(ret)
        {
            for(int p=i;p<m_length-1;p++)
            {
                m_array[p] = m_array[p + 1];
            }
            m_length--;
        }
        return ret;
    }

    bool get(int i,T& obj) const
    {
        bool ret = ((0 <= i) && (i < m_length));
        if(ret)
        {
            obj = m_array[i];
        }
        return ret;

    }
    bool set(int i, const T& obj)
    {
        bool ret = ((0 <= i) && (i < m_length));
        if(ret)
        {
            m_array[i] = obj;
        }
        return ret;
    }

    int length() const
    {
        return m_length;
    }
    void clear()
    {
        m_length = 0;
    }

    T& operator[] (int i)
    {
        bool ret = ((0 <= i) && (i < m_length));
        if(ret)
        {
            return m_array[i];
        }
        else
        {
            THROWEXCEPTION(IndexOutOfBoundsException,"parameter i is invalid");
        }
    }

    T operator[] (int i) const
    {
        return (const_cast<SeqList<T>&>(*this))[i];
    }

    virtual int capacity() const = 0;   //顺序存储空间的容量

};

}




#endif // SEQLIST_H
