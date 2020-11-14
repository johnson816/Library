#include <iostream>
#include "JSString.h"
#include <cstring>
#include <cstdlib>

using namespace std;
using namespace JSLib;



int main()
{
    String str = "abcde";
    String s1 = str.sub(0,1);
    cout << str.str() << endl;
    cout << s1.str() << endl;
    cout << s1.length() << endl;
    return 0;
}


















