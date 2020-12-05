#include <iostream>
#include "GTreeNode.h"
#include "GTree.h"

using namespace std;
using namespace JSLib;



int main()
{
    GTreeNode<char>* tn = NULL;
    GTree<char> tt;

    GTreeNode<char> gtn;
    gtn.value = 'A';

    tt.insert(&gtn);
    tn = tt.find('A');
    tt.insert('B',tn);
    tt.insert('C',tn);
    tt.insert('D',tn);


    tn = tt.find('B');
    tt.insert('E',tn);
    tt.insert('F',tn);



    tn = tt.find('E');
    tt.insert('K',tn);
    tt.insert('L',tn);

    tn = tt.find('C');
    tt.insert('G',tn);

    tn = tt.find('D');
    tt.insert('H',tn);
    tt.insert('I',tn);
    tt.insert('J',tn);


    tn = tt.find('H');
    tt.insert('M',tn);

    cout << tt.count() << endl;
    cout << tt.height() << endl;
    cout << tt.degree() << endl;

    for(tt.begin();!tt.end();tt.next())
    {
        cout << tt.current() << endl;
    }
    return 0;
}


















