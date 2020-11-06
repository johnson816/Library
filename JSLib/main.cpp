#include <iostream>
#include "LinkStack.h"

using namespace std;
using namespace JSLib;

bool is_left(char c)
{
    return (c == '{') || (c == '[') || (c == '<') || (c == '(');
}

bool is_right(char c)
{
    return (c == '}') || (c == ']') || (c == '>') || (c == ')');
}

bool is_quot(char c)
{
    return (c == '\'') || (c == '\"');
}

bool is_match(char l,char r)
{
    return ((l == '{') && (r== '}')) ||
           ((l == '[') && (r== ']')) ||
           ((l == '<') && (r== '>')) ||
           ((l == '(') && (r== ')')) ||
           ((l == '\'') && (r== '\'')) ||
           ((l == '\"') && (r== '\"')) ;

}

bool scan(const char* code)
{
    LinkStack<char>stack;
    int i= 0;
    bool ret = true;

    code = (code == NULL) ? "" : code;

    while(ret && (code[i] != '\0'))
    {
        if(is_left(code[i]))
        {
            stack.push(code[i]);
        }
        else if(is_right(code[i]))
        {
            if((stack.size() > 0) && is_match(stack.top(),code[i]))
            {
                stack.pop();
            }
            else
            {
                ret = false;
                break;
            }
        }
        else if(is_quot(code[i]))
        {
            if(stack.size() == 0 || !is_match(stack.top(),code[i]))
            {
                stack.push(code[i]);
            }
            else if(is_match(stack.top(),code[i]))
            {
                stack.pop();
            }
        }
        i++;
    }
    return ret && (stack.size() == 0);
}

int main()
{

    cout << scan("else if(is_quot(code[i])){if(stack.size() == 0 || !is_match(stack.top(),code[i])){stack.push(code[i]);}else if(is_match(stack.top(),code[i])){stack.pop();}}") << endl;


    return 0;
}
