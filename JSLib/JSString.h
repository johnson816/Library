#ifndef JSSTRING_H
#define JSSTRING_H

#include "Object.h"

namespace JSLib
{

class String : public Object
{

protected:
    char* m_str;
    int m_length;

    void init(const char* s);                                    //初始化字符串对象
    bool equal(const char* s,const char* l,int len) const;        //判断字符是否相等
public:
    String();
    String(const char* s);
    String(char c);
    String(const String &s);
    int length() const;
    const char* str() const;                                     //获取字符串对象内部的具体字符串
    static int* make_pmt(const char* s);                         //求得KMP算法中的子串的部分匹配表
    static int kmp(const char* s,const char* p);                 //KMP子串查找函数

    bool startWith(const String& s) const;                       //判断字符串是否以字符串s开头
    bool startWith(const char* s)const;
    bool endOf(const char* s) const;                             //判断字符串是否以字符串s结尾
    bool endOf(const String& s) const;
    String& insert(int i,const char* s);
    String& insert(int i,const String& s);
    String& trim();                                              //清空字符串两端的空格字符串
    int indexOf(const char* s) const;                            //查找子字符串s在字符串对象中的位置
    int indexOf(const String& s)const;
    String& remove(int i,int len);                               //在i处将长度为len的字符串删除
    String& remove(const char* s);                               //将子字符串s删除
    String& remove(const String& s);
    String& replace(const char* str,const String& s);            //将字符串str所在的位置用s替代
    String& replace(const char* str,const char* s);
    String& replace(const String& s,const char* str);
    String& replace(const String& str,const String& s);
    String sub(int i,int len) const;                            //在字符串i处创建一个长度为len的子串返回

    char& operator [] (int i);
    char operator[] (int i) const;
    bool operator == (const String& s) const;
    bool operator == (const char* s) const;
    bool operator != (const String& s) const;
    bool operator != (const char* s) const;
    bool operator >  (const String& s) const;
    bool operator >  (const char* s) const;
    bool operator <  (const String& s) const;
    bool operator <  (const char* s) const;
    bool operator >= (const String& s) const;
    bool operator >= (const char* s) const;
    bool operator <= (const String& s) const;
    bool operator <= (const char* s) const;

    String operator +  (const String& s) const;
    String operator +  (const char* s) const;
    String& operator +=(const String& s);
    String& operator +=(const char* s);

    String operator -  (const String& s) const;
    String operator -  (const char* s) const;
    String& operator -=(const String& s);
    String& operator -=(const char* s);

    String& operator = (const String& s);
    String& operator = (const char* s);
    String& operator = (char c);

    ~String();

};

}


#endif // JSSTRING_H
