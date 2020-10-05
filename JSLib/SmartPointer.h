#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Object.h"

namespace JSLib
{

template
<typename T>
class SmartPointer : public Object
{
protected:
    T* m_pointer;
public:
    SmartPointer(T* sp = NULL)
    {
        m_pointer = sp;
    }
    SmartPointer(const SmartPointer<T>& obj)
    {
        m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
    }
    SmartPointer<T>& operator =(const SmartPointer<T>& obj)
    {
        if(this != &obj)
        {
            delete m_pointer;
            m_pointer = obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
        }
        return *this;
    }
    T* operator ->()
    {
        return m_pointer;
    }
    T& operator*()
    {
        return *m_pointer;
    }
    bool is_null()
    {
        return(NULL == m_pointer);
    }
    T* get_pointer()
    {
        return m_pointer;
    }
    ~SmartPointer()
    {
        delete m_pointer;
    }
};

}


#endif // SMARTPOINTER_H
