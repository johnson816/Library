#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace JSLib
{

template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;
    T* Copy(T* array,int length,int new_length)
    {
        T* ret = new T[new_length];
        if(ret != NULL)
        {
            for(int i=0;i<new_length;i++)
            {
                int size = (length < new_length) ? length : new_length;
                for(int i=0;i<size;i++)
                {
                    ret[i] = array[i];
                }
            }
        }
        else
        {
            THROWEXCEPTION(NoEnoughMemoryException,"No memory to creat DynamicArray");
        }
        return ret;
    }
    void update(T* array,int length)
    {
        T* tem = this->m_array;
        if(tem != NULL)
        {
            this->m_array = array;
            this->m_length = length;
            delete[] tem;
        }
        else
        {
            THROWEXCEPTION(NoEnoughMemoryException,"No memory to creat DynamicArray");
        }
    }
    void Init(T* array,int length)
    {
        if(array != NULL)
        {
            this->m_array = array;
            this->m_length = length;
        }
        else
        {
            THROWEXCEPTION(NoEnoughMemoryException,"No memory to creat DynamicArray");
        }
    }

public:
    DynamicArray(int length = 0)
    {
        Init(new T[length],length);
    }

    DynamicArray(const DynamicArray<T>& obj)
    {
        Init(Copy(obj.m_array,obj.m_length,obj.m_length),obj.m_length);
    }

    DynamicArray<T>& operator =(const DynamicArray<T>& obj)
    {
        if(this != &obj)
        {
            update(Copy(obj.m_array,obj.m_length,obj.m_length),obj.m_length);
        }

        return *this;
    }

    int length() const
    {
        return this->m_length;
    }
    void resize(int length)
    {
        if(length != this->m_length)
        {
            update(Copy(this->m_array,this->m_length,length),length);
        }
    }

    ~DynamicArray()
    {
        delete[] this->m_array;
    }
};


}




#endif // DYNAMICARRAY_H
