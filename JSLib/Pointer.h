#ifndef POINTER_H
#define POINTER_H

#include "Object.h"

namespace JSLib
{

template < typename T >
class Pointer : public Object
{
protected:
    T* m_pointer;
public:
    Pointer(T* pointer = NULL)
    {
        m_pointer = pointer;
    }
    T* operator ->()
    {
        return m_pointer;
    }
    T& operator * ()
    {
        return *m_pointer;
    }
    T* operator ->() const
    {
        return m_pointer;
    }
    const T& operator * () const
    {
        return *m_pointer;
    }
    bool isNull() const
    {
        return (m_pointer == NULL);
    }
    T* get() const
    {
        return m_pointer;
    }
};

}



#endif // POINTER_H
