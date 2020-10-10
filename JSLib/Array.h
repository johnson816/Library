#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"
#include "Exception.h"

namespace JSLib
{

template <typename T>
class Array : public Object
{
protected:
    T* m_array;
public:
    bool set(int i,const T& obj)
    {
        bool ret = ((0 <= i) && (i < this->length()));
        if(ret)
        {
            m_array[i] = obj;
        }
        return ret;
    }
    bool get(int i,T& obj) const
    {
        bool ret = ((0 <= i) && (i < this->length()));
        if(ret)
        {
            obj = m_array[i];
        }
        return ret;
    }
    T& operator [](int i)
    {
        if((0 <= i) && (i < this->length()))
        {
            return m_array[i];
        }
        else
        {
            THROWEXCEPTION(IndexOutOfBoundsException,"Parameter i is invalid");
        }
    }
    T operator[](int i) const
    {
        return (const_cast<Array<T>&>(*this))[i];
    }
    virtual int length() const = 0;
};

}



#endif // ARRAY_H
