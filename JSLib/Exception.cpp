#include "Exception.h"
#include <cstdlib>
#include <cstring>
#include <stdio.h>



using namespace std;

namespace JSLib
{

    /****当m_location通过malloc申请堆内存失败时，直接让其等于NULL即可****/
    /****若添加else语句抛出NoEnoughMemoryException异常，则有两点错误****/
    /****第一：父对象无法构建完成，但是却抛出了子类异常               ****/
    /****第二：要构建子类对象，就要调用子类构造函数，子类构造函数会调用 ****/
    /****父类构造函数，最后将会调用Init函数，因为Init函数无法申请得到足****/
    /****够的堆内存而造成死循环                                    ****/
void Exception::Init(const char* message,const char* file,int line)
{
    m_message = strdup(message);
    if(file != NULL)
    {
        char ac[16];
        sprintf(ac,"%d",line);
        m_location = reinterpret_cast<char*>(malloc(strlen(file)+strlen(ac)+2)); //+2一个字节放":",另一个放'\0'
        if(m_location != NULL)
        {
            m_location = strcpy(m_location,file);
            m_location = strcat(m_location,":");
            m_location = strcat(m_location,ac);
        }

    }
    else
    {
        m_location = NULL;
    }
}

Exception::Exception(const char* message)
{
    Init(message,NULL,0);
}

Exception::Exception(const char* file,int line)
{
    Init(NULL,file,line);
}

Exception::Exception(const char* message,const char* file,int line)
{
    Init(message,file,line);
}

Exception::Exception(const Exception& e)
{
    m_message = strdup(e.m_message);
    m_location = strdup(e.m_location);
}

Exception& Exception::operator =(const Exception& e)
{
    if(this != &e)
    {
        free(m_message);
        free(m_location);
        m_message = strdup(e.m_message);
        m_location = strdup(e.m_location);
    }
    return *this;
}

const char* Exception::message() const
{
    return m_message;
}
const char* Exception::location() const
{
    return m_location;
}

Exception::~Exception()
{
    free(m_message);
    free(m_location);
}

}
