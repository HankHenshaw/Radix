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

   std::cout << tree.find("romanusus") << '\n';
   std::cout << tree.find("romanusis") << '\n';
   std::cout << tree.find("romane") << '\n';
   std::cout << tree.find("romanus") << '\n';
   std::cout << tree.find("roma") << '\n';
   std::cout << tree.find("oma") << '\n';

    std::cout << "Done\n";
    return 0;
}
