#ifndef QUEUE_H
#define QUEUE_H

#include "Object.h"

namespace JSLib
{

template < typename T>
class Queue : public Object
{
public:
    virtual void add(const T& e) = 0;           //入队列
    virtual void remove() = 0;                  //出队列
    virtual T front() const = 0;                //获取队头的元素
    virtual void clear() = 0;                   //清空队列
    virtual int length() const = 0;             //获取队列的长度
};


}

#endif // QUEUE_H
