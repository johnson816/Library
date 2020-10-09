#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"
#include "Exception.h"

namespace JSLib
{

template<typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;
public:
    DynamicList(int capacity)
    {
        T* array = new T[capacity];
        if(array != NULL)
        {
            this->m_array = array;
            this->m_length = 0;
            this->m_capacity = capacity;
        }
        else
        {
            THROWEXCEPTION(NoEnoughMemoryException,"No memmory to creat DynamicList");
        }
    }
    int capacity() const
    {
        return this->m_capacity;
    }
    void resize(int capacity)
    {
        if(capacity != this->m_capacity)
        {
            T* array = new T[capacity];
            if(array != NULL)
            {
                int length = (capacity > this->m_length ? this->m_length : capacity);
                for(int i=0;i<length;i++)
                {
                    array[i] = this->m_array[i];
                }
                T* tem = this->m_array;                  //不直接先释放m_array,使函数异常安全
                this->m_array = array;
                this->m_length = length;
                this->m_capacity = capacity;
                delete[] tem;
            }
            else
            {
                THROWEXCEPTION(NoEnoughMemoryException,"No memmory to resize DynamicList");
            }
        }
    }
    ~DynamicList()
    {
        delete[] this->m_array;
    }
};

}


#endif // DYNAMICLIST_H
