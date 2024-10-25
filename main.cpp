#include "iter_tree.hpp"
#include <iostream>
#include <vector>



int main()
{
    Tree<int> t{};
    t.insert(5);
    std::cout << t.height <<std::endl;
    t.insert(3);
    std::cout << t.height << std::endl;
    t.insert(8);
    std::cout << t.height << std::endl;
    t.insert(1);
    std::cout << t.height << std::endl;
    t.insert(9);
    std::cout << t.height << std::endl;
    t.insert(17);
    std::cout << t.height << std::endl;
    std::cout << t << std::endl;
}