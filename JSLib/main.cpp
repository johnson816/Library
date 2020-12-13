#include <iostream>
#include "BTree.h"

using namespace std;
using namespace JSLib;



int main()
{

    BTree<int>bt;
    TreeNode<int>* btn = NULL;


    bt.insert(1,NULL);

    btn = bt.find(1);
    bt.insert(2,btn);
    bt.insert(3,btn);

    btn = bt.find(2);
    bt.insert(4,btn);
    bt.insert(5,btn);

    btn = bt.find(4);
    bt.insert(8,btn);
    bt.insert(9,btn);

    btn = bt.find(5);
    bt.insert(10,btn);

    btn = bt.find(3);
    bt.insert(6,btn);
    bt.insert(7,btn);

    cout << bt.count() << endl;
    cout << bt.height() << endl;
    cout << bt.degree() << endl;


    SharedPointer< Array<int> > n = bt.traversal(LevelOrder);

    for(int i=0;i<n->length();i++)
    {
        cout << (*n)[i] << " ";
    }
    cout << endl;

    BTreeNode<int>* bNthread = bt.thread(LevelOrder);

    while( bNthread->right != NULL )
    {
        bNthread = bNthread->right;
    }

    while( bNthread )
    {
        cout << bNthread->value << " ";
        bNthread = bNthread->left;
    }
    cout << endl;
/*
    int a[] = {8,9,10,6,7};

    for(int i=0;i<5;i++)
    {
        TreeNode<int>* node = bt.find(a[i]);

        while( node )
        {
            cout << node->value << " ";
            node = node->parent;
        }

        cout << endl;
    }*/



    return 0;
}


















