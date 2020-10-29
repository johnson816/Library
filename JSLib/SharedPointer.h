#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "Pointer.h"
#include <cstdio>
#include "Exception.h"
namespace JSLib
{

template <typename T>
class SharedPointer : public Pointer<T>
{
protected:
    int* m_ref;
    void assign(const SharedPointer<T>& obj)
    {
        this->m_pointer = obj.m_pointer;
        this->m_ref = obj.m_ref;
        if(this->m_ref)
        {
            (*(this->m_ref))++;
        }
    }

public:
    SharedPointer(T* p = NULL) : m_ref(NULL)
    {
        if(p != NULL)
        {
            this->m_ref = static_cast<int*>(std::malloc(sizeof(int)));
            if(this->m_ref != NULL)
            {
                this->m_pointer = p;
                (*(this->m_ref)) = 1;
            }
            else
            {
                THROWEXCEPTION(NoEnoughMemoryException,"No memory to creat SharedPointer Object");
            }
        }
    }

    SharedPointer(const SharedPointer& obj) : Pointer<T>(NULL)
    {
        this->m_pointer = obj.m_pointer;
        assign(obj);
    }

    SharedPointer<T>& operator =(const SharedPointer<T>& obj)
    {
        if(this != &obj)
        {
            clear();
            assign(obj);
        }
        return *this;
    }

    void clear()
    {
        T* toDel = this->m_pointer;
        int* ref = this->m_ref;
        this->m_pointer = NULL;
        this->m_ref = NULL;
        if(ref)
        {
            (*ref)--;
            if(0 == *ref)
            {
                free(ref);
                delete toDel;
            }
        }
    }
    int getRef()
    {
        return *m_ref;
    }

    ~SharedPointer()
    {
        clear();
    }

};

template <typename T>
bool operator ==(const SharedPointer<T>l,const SharedPointer<T>r)
{
    return (l.get()== r.get());
}
template <typename T>
bool operator !=(const SharedPointer<T>l,const SharedPointer<T>r)
{
    return (!(l == r));
}

}

#endif // SHAREDPOINTER_H
