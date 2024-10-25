#include "iter_tree.hpp"
#include <iostream>
#include <vector>

int main()
{
    Tree<std::pair<int,int>> t{};
    t.emplace(1,2);
    t.emplace(2,4);
    t.emplace(3,8);    
    std::cout << t << std::endl;
}