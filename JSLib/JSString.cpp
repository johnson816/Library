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

bool String::equal(const char* s,const char* l,int len) const
{
    bool ret =true;
    for(int i=0;i<len && ret;i++)
    {
        ret = ret && (s[i] == l[i]);
    }
    return ret;
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

int* String::make_pmt(const char* s)
{
    int len = strlen(s);
    int* ret = reinterpret_cast<int*>(malloc(sizeof(int) * len));    //部分匹配表
    if(ret != NULL)
    {
        int ll = 0;                                             //KMP算法中部分匹配表的部分匹配值
        ret[0] = 0;
        for(int i=1;i<len;i++)
        {
            while((ll > 0) && (s[i] != s[ll]))
            {
                ll = ret[ll - 1];
            }
            if(s[ll] == s[i])
            {
                ll++;
            }
            ret[i] = ll;
        }
    }

    return ret;

}

int String::kmp(const char* s,const char* p)
{
    int ret = -1;
    int sl = strlen(s);
    int pl = strlen(p);
    int* pmt = make_pmt(p);

    if((pmt != NULL) && (pl > 0) && (pl < sl))
    {
        for(int i=0,j=0;i<sl;i++)
        {
            while((j > 0) && (p[j] != s[i]))
            {
                j = pmt[j - 1];                         //移动字符串
            }

            if(p[j] == s[i])
            {
                j++;
            }
            if(j == pl)
            {
                ret = i + 1 - j;
                break;
            }

        }
    }

    return ret;
}

bool String::startWith(const String& s) const
{
    return startWith(s.m_str);
}

bool String::startWith(const char* s)const
{
    bool ret = (s != NULL);

    if(ret)
    {
        int len = strlen(s);
        ret = (len <= m_length) && (equal(m_str,s,len));
    }
    return ret;
}

bool String::endOf(const char* s) const
{
    bool ret = (s != NULL);

    if(ret)
    {

        int len = strlen(s);
        char* str = m_str + (m_length - len);
        ret = (len <= m_length) && equal(str,s,len);
    }
    return ret;
}

bool String::endOf(const String& s) const
{
    return endOf(s.m_str);
}

String& String::insert(int i,const char* s)
{
    if((0 <= i) && (i <= m_length))
    {
        if( (s[0] != '\0') && (s != NULL))
        {
            char* str = reinterpret_cast<char*>(malloc(m_length + strlen(s) + 1));
            if(str != NULL)
            {
                strncpy(str,m_str,i);
                strncpy(str + i,s,strlen(s));
                strncpy(str + i + strlen(s),m_str + i,m_length - i);
                str[m_length + strlen(s)] = '\0';

                free(m_str);
                m_str = str;
                m_length = m_length + strlen(s);
            }
            else
            {
                THROWEXCEPTION(NoEnoughMemoryException,"No memory to insert String value");
            }
        }

    }
    else
    {
        THROWEXCEPTION(InvalidOperationException,"Parameter i is invalid");
    }

    return *this;
}

String& String::insert(int i,const String& s)
{
    return insert(i,s.m_str);
}

String& String::trim()
{
    int front = 0;                          //标识第一次到达非空格字符串的位置
    int end = m_length - 1;                 //标识字符串和空格字符串的边界
    while(m_str[front] == ' ') front++;
    while(m_str[end] == ' ') end--;
    if(0 == front)
    {
        m_str[end + 1] = '\0';
        m_length = end + 1;
    }
    else
    {
        for(int i=0,j=front;j<=end;j++,i++)
        {
            m_str[i] = m_str[j];
        }
        m_str[end - front + 1] = '\0';
        m_length = end - front + 1;
    }

    return *this;
}

int String::indexOf(const char* s) const
{
    return kmp(m_str,s);
}

int String::indexOf(const String& s)const
{
    return kmp(m_str,s.m_str);
}

String& String::remove(int i,int len)
{
    if((0 <= i) && (i < m_length))
    {
        int n = i;
        int m = len + i;
        while((n < m) && (m < m_length))
        {
            m_str[n++] = m_str[m++];
        }

        m_str[n] = '\0';
        m_length = n;
    }
    else
    {
        THROWEXCEPTION(IndexOutOfBoundsException,"Parameter i is invalid");
    }
    return *this;
}

String& String::remove(const char* s)
{
    return remove(kmp(m_str,s),strlen(s));
}

String& String::remove(const String& s)
{
    return remove(s.m_str);
}

String& String::replace(const char* str,const String& s)     //将字符串str所在的位置用s替代
{
    return replace(str,s.m_str);
}

String& String::replace(const char* str,const char* s)     //将字符串str所在的位置用s替代
{
    int index = kmp(m_str,str);
    if(index >= 0)
    {
        remove(str);
        insert(index,s);
    }
    return *this;

}

String& String::replace(const String& s,const char* str)
{
    return replace(s.m_str,str);
}

String& String::replace(const String& str,const String& s)
{
    return replace(str.m_str,s.m_str);
}

String String::sub(int i,int len) const
{
    String ret;
    if((0 <= i) && (i < m_length))
    {
        if(len < 0) len = 0;
        if(len + i > m_length) len = m_length - i;
        char* s = reinterpret_cast<char*>(malloc(len + 1));
        strncpy(s,m_str+i,len);

        s[len] = '\0';
        ret.m_str = s;
        ret.m_length = len;
    }
    else
    {
        THROWEXCEPTION(IndexOutOfBoundsException,"Parameter i is invalid");
    }

    return ret;
}

char& String::operator [] (int i)
{
    if((0 <= i) && (i < m_length))
    {
        return m_str[i];
    }
    else
    {
        THROWEXCEPTION(IndexOutOfBoundsException,"Parameter i is invalid");
    }

}

char String::operator[] (int i) const
{
    return (const_cast<String&>(*this))[i];
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


String String::operator -  (const String& s) const
{
    return String(*this).remove(s);
}

String String::operator -  (const char* s) const
{
    return String(*this).remove(s);
}

String& String::operator -=(const String& s)
{
    return remove(s);
}

String& String::operator -=(const char* s)
{
    return remove(s);
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
            free(m_str);
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




