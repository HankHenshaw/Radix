#include <iostream>
#include <algorithm>
#include "radixtree.h"

int main()
{
    RadixTree tree;
    tree.insert("romanusus");
    tree.insert("romanusis");
    tree.insert("romane");
    tree.insert("romanus");
//    tree.insert("omar");
//    tree.insert("max");
//    tree.insert("maxim");
//    tree.insert("jackob");
//    tree.insert("jack");

    std::cout << "Done\n";
    return 0;
}
