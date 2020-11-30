#include <iostream>
#include "Sort.h"
#include "StaticArray.h"
#include "ctime"

using namespace std;
using namespace JSLib;

struct Test : public Object
{
    int id;
    int data1[1000];
    double data2[1000];

    bool operator < (Test& obj)
    {
        return (id < obj.id);
    }

    bool operator >= (Test& obj)
    {
        return (id >= obj.id);
    }

    bool operator > (Test& obj)
    {
        return (id > obj.id);
    }

    bool operator <= (Test& obj)
    {
        return (id <= obj.id);
    }
};

struct TestProxy : public Object
{
protected:
    Test* m_pTest;

public:
    int id()
    {
        return m_pTest->id;
    }

    int* data1()
    {
        return m_pTest->data1;
    }

    double* data2()
    {
        return m_pTest->data2;
    }


    bool operator < (TestProxy& obj)
    {
        return (*m_pTest < *(obj.m_pTest));
    }

    bool operator >= (TestProxy& obj)
    {
        return (*m_pTest >= *(obj.m_pTest));
    }

    bool operator > (TestProxy& obj)
    {
        return (*m_pTest > *(obj.m_pTest));
    }

    bool operator <= (TestProxy& obj)
    {
        return (*m_pTest <= *(obj.m_pTest));
    }

    Test& operator =(Test& obj)
    {
        m_pTest = &obj;
        return obj;
    }

};

Test test[1000];
TestProxy testproxy[1000];

int main()
{
    clock_t begin = 0;
    clock_t end = 0;

    for(int i=0;i<1000;i++)
    {
        test[i].id = i;
        testproxy[i] = test[i];
    }

    begin = clock();

    Sort::Bubble(testproxy,1000,false);

    end = clock();

    cout << "Time = " << (end - begin) << endl;
    for(int i=0;i<1000;i++)
    {
        cout << test[i].id << " " << testproxy[i].id() << endl;
    }

    return 0;
}


















