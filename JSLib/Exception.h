#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <cstdlib>
#include "Object.h"

namespace JSLib
{

    /****若无法使用throw，则将THROWEXCEPTION(e,message)定义为空****/
#define THROWEXCEPTION(e,message)  (throw e(message,__FILE__,__LINE__))

class Exception : public Object
{
protected:
    char* m_message;
    char* m_location;
    void Init(const char* message,const char* file,int line);
public:
    Exception(const char* message);
    Exception(const char* file,int line);
    Exception(const char* message,const char* file,int line);

    Exception(const Exception& e);
    Exception& operator =(const Exception& e);

    virtual const char* message() const;
    virtual const char* location() const;

    virtual ~Exception() = 0;
};

class ArithmeticException:public Exception
{
public:
    ArithmeticException() :Exception(NULL) {}
    ArithmeticException(const char* message) :Exception(message) {}
    ArithmeticException(const char* file,int line) : Exception(file,line){}
    ArithmeticException(const char* message,const char* file,int line) : Exception(message,file,line) {}

    ArithmeticException(const ArithmeticException& ar) : Exception(ar){}
    ArithmeticException& operator =(const ArithmeticException& ar)
    {
        if(this != &ar)
        {
            free(m_message);
            free(m_location);
            m_message = ar.m_message;
            m_location = ar.m_location;
        }
        return *this;
    }


};

class NullPointerException:public Exception
{
public:
    NullPointerException() :Exception(NULL) {}
    NullPointerException(const char* message) :Exception(message) {}
    NullPointerException(const char* file,int line) : Exception(file,line){}
    NullPointerException(const char* message,const char* file,int line) : Exception(message,file,line) {}

    NullPointerException(const NullPointerException& ar) : Exception(ar){}
    NullPointerException& operator =(const NullPointerException& ar)
    {
        if(this != &ar)
        {
            free(m_message);
            free(m_location);
            m_message = ar.m_message;
            m_location = ar.m_location;
        }
        return *this;
    }


};

class IndexOutOfBoundsException:public Exception
{
public:
    IndexOutOfBoundsException() :Exception(NULL) {}
    IndexOutOfBoundsException(const char* message) :Exception(message) {}
    IndexOutOfBoundsException(const char* file,int line) : Exception(file,line){}
    IndexOutOfBoundsException(const char* message,const char* file,int line) : Exception(message,file,line) {}

    IndexOutOfBoundsException(const IndexOutOfBoundsException& ar) : Exception(ar){}
    IndexOutOfBoundsException& operator =(const IndexOutOfBoundsException& ar)
    {
        if(this != &ar)
        {
            free(m_message);
            free(m_location);
            m_message = ar.m_message;
            m_location = ar.m_location;
        }
        return *this;
    }


};

class NoEnoughMemoryException:public Exception
{
public:
    NoEnoughMemoryException() :Exception(NULL) {}
    NoEnoughMemoryException(const char* message) :Exception(message) {}
    NoEnoughMemoryException(const char* file,int line) : Exception(file,line){}
    NoEnoughMemoryException(const char* message,const char* file,int line) : Exception(message,file,line) {}

    NoEnoughMemoryException(const NoEnoughMemoryException& ar) : Exception(ar){}
    NoEnoughMemoryException& operator =(const NoEnoughMemoryException& ar)
    {
        if(this != &ar)
        {
            free(m_message);
            free(m_location);
            m_message = ar.m_message;
            m_location = ar.m_location;
        }
        return *this;
    }
};

class InvalidParameterException:public Exception
{
public:
    InvalidParameterException() :Exception(NULL) {}
    InvalidParameterException(const char* message) :Exception(message) {}
    InvalidParameterException(const char* file,int line) : Exception(file,line){}
    InvalidParameterException(const char* message,const char* file,int line) : Exception(message,file,line) {}

    InvalidParameterException(const InvalidParameterException& ar) : Exception(ar){}
    InvalidParameterException& operator =(const InvalidParameterException& ar)
    {
        if(this != &ar)
        {
            free(m_message);
            free(m_location);
            m_message = ar.m_message;
            m_location = ar.m_location;
        }
        return *this;
    }
};

class InvalidOperationException:public Exception
{
public:
    InvalidOperationException() :Exception(NULL) {}
    InvalidOperationException(const char* message) :Exception(message) {}
    InvalidOperationException(const char* file,int line) : Exception(file,line){}
    InvalidOperationException(const char* message,const char* file,int line) : Exception(message,file,line) {}

    InvalidOperationException(const InvalidOperationException& ar) : Exception(ar){}
    InvalidOperationException& operator =(const InvalidOperationException& ar)
    {
        if(this != &ar)
        {
            free(m_message);
            free(m_location);
            m_message = ar.m_message;
            m_location = ar.m_location;
        }
        return *this;
    }
};

}

#endif // EXCEPTION_H
