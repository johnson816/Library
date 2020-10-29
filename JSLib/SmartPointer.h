#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Pointer.h"

namespace JSLib
{

template
<typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* sp = NULL) : Pointer<T>::Pointer(sp)
    {

    }
    SmartPointer(const SmartPointer<T>& obj)
    {
        this->m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
    }
    SmartPointer<T>& operator =(const SmartPointer<T>& obj)
    {
        if(this != &obj)
        {
            T* tem = this->m_pointer;
            this->m_pointer = obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
            delete tem;
        }
        return *this;
    }
    ~SmartPointer()
    {
        delete this->m_pointer;
    }
};

}


#endif // SMARTPOINTER_H
