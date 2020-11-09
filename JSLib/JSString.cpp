#include "JSString.h"
#include <cstring>
#include <cstdlib>
#include "Exception.h"

using namespace std;

namespace JSLib
{

void String::init(const char *s)
{
    m_str = strdup(s);
    if(m_str)
    {
        m_length = strlen(m_str);
    }
    else
    {
        THROWEXCEPTION(NoEnoughMemoryException,"No memory to creat String Object");
    }
}

String::String()
{
    init("");
}

String::String(char c)
{
    char str[] = {c,'\0'};
    init(str);
}

String::String(const char* s)
{
    init(s ? s : "");
}

String::String(const String &s)
{
    init(s.m_str);
}

int String::length() const
{
    return m_length;
}

const char* String::str() const
{
    return m_str;
}

bool String::operator == (const String& s) const
{
    return (strcmp(m_str,s.m_str) == 0);
}

bool String::operator == (const char* s) const
{
    return (strcmp(m_str,s ? s : "") == 0);
}

bool String::operator != (const String& s) const
{
    return !(*this == s);
}

bool String::operator != (const char* s) const
{
    return !(*this == s ? s : "");
}

bool String::operator > (const String& s) const
{
    return (strcmp(m_str,s.m_str) > 0);
}

bool String::operator > (const char* s) const
{
    return (strcmp(m_str,s ? s : "") > 0);
}

bool String::operator < (const String& s) const
{
    return (strcmp(m_str,s.m_str) < 0);
}
bool String::operator < (const char* s) const
{
    return (strcmp(m_str,s ? s : "") < 0);
}

bool String::operator >= (const String& s) const
{
    return (strcmp(m_str,s.m_str) >= 0);
}

bool String::operator >= (const char* s) const
{
    return (strcmp(m_str,s ? s : "") >= 0);
}

bool String::operator <= (const String& s) const
{
    return (strcmp(m_str,s.m_str) <= 0);
}

bool String::operator <= (const char* s) const
{
    return (strcmp(m_str,s ? s : "") <= 0);
}

String String::operator + (const String& s) const
{
    return (*this + s.m_str);
}

String String::operator + (const char* s) const
{
    String ret;
    int length = m_length + strlen(s ? s : "");
    char* tem = reinterpret_cast<char*>(malloc(length + 1));
    if(tem != NULL)
    {
        strcpy(tem,m_str);
        strcat(tem,s ? s : "");
        ret.m_str = tem;
        ret.m_length = length;
    }
    else
    {
        THROWEXCEPTION(NoEnoughMemoryException,"No memory to add String");
    }

    return ret;
}

String& String::operator +=(const String& s)
{
    return (*this = *this + s);
}

String& String::operator +=(const char* s)
{
    return (*this = *this + s);
}

String& String::operator = (const String& s)
{
    return(*this = s.m_str);
}

String& String::operator = (const char* s)
{
    if(m_str != s)
    {
        char* str = strdup(s);
        if(str != NULL)
        {
            m_str = str;
            m_length = strlen(str);
        }
        else
        {
            THROWEXCEPTION(NoEnoughMemoryException,"No enough memory to assign new String");
        }
    }
    return *this;
}

String& String::operator = (char c)
{
    char str[] = {c,'\0'};
    return (*this = str);
}

String::~String()
{
    free(m_str);
}

}




