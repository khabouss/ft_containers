// Copyright 2022 Taha Khabouss
#include <iostream>
#include "../src/vector/vector.hpp"

int main() {
    std::cout << "------------- MAIN -------------" << std::endl;

    ft::vector<int> first;


    first.assign(7, 100);  // 7 ints with a value of 100

    ft::iterator<ft::random_access_iterator_tag, int> it;
    it = first.begin();

    first.assign(it, it + 2);

    // std::cout << *it << std::endl;

    std::cout << "------------- MAIN -------------" << std::endl;
    return (0);
}
