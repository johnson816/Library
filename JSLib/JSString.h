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

    void init(const char* s);
public:
    String();
    String(const char* s);
    String(char c);
    String(const String &s);
    int length() const;
    const char* str() const;

    bool operator == (const String& s) const;
    bool operator == (const char* s) const;
    bool operator != (const String& s) const;
    bool operator != (const char* s) const;
    bool operator > (const String& s) const;
    bool operator > (const char* s) const;
    bool operator < (const String& s) const;
    bool operator < (const char* s) const;
    bool operator >= (const String& s) const;
    bool operator >= (const char* s) const;
    bool operator <= (const String& s) const;
    bool operator <= (const char* s) const;

    String operator + (const String& s) const;
    String operator + (const char* s) const;
    String& operator +=(const String& s);
    String& operator +=(const char* s);

    String& operator = (const String& s);
    String& operator = (const char* s);
    String& operator = (char c);

    ~String();

};

}


#endif // JSSTRING_H
