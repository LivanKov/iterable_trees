#include "iter_tree.hpp"
#include <iostream>
#include <vector>
#include <print>


struct test_struct
{
    int a;
    int b;
    int c;

    test_struct(int a, int b, int c) : a{a}, b{b}, c{c} {}
};


int main()
{


    std::vector<test_struct>v{};
    v.emplace_back(1,2,3);
    v.emplace_back(std::move(test_struct(4,5,6)));
    std::println("{}",v.size());
    std::println("{}",v[0].a);
    std::println("{}",v[0].b);
    std::println("{}",v[0].c);
    /*Tree<int> t{};
    t.insert(5);
    t.insert(3);
    t.insert(8);
    t.insert(1);
    t.insert(9);
    t.insert(17);
    std::cout << t << std::endl;*/
}