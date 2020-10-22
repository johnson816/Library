#include <iostream>
#include "LinkList.h"

using namespace std;
using namespace JSLib;



int main()
{
    LinkList<int>list;
    for(int i=0;i<5;i++)
    {
        list.insert(i);
    }

    for(list.move(0);!list.end();list.next())
    {
        cout << list.current() << endl;
    }
    return 0;
}
