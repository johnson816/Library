#include "Object.h"
#include <cstdlib>
#include <iostream>

using namespace std;

namespace JSLib
{

void* Object::operator new (unsigned int size) throw()
{
    return malloc(size);
}

void Object::operator delete(void* p)
{
    free(p);
    p = NULL;
}

void* Object::operator new[](unsigned int size) throw()
{
    return malloc(size);
}
void Object::operator delete[](void* p)
{
    free(p);
    p = NULL;
}

Object:: ~Object()
{

}

}
