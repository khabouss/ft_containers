// Copyright 2022 Taha Khabouss
#include "main.hpp"

int main() {
    std::cout << "------------- MAIN -------------" << std::endl;

    ft::vector<int> first;
    ft::vector<int> second;
    ft::vector<int> third;

    first.assign(7, 100);  // 7 ints with a value of 100

    ft::iterator<ft::random_access_iterator_tag, int> it;
    it = first.begin() + 1;

    second.assign(it, first.end() - 1);  // the 5 central values of first

    int myints[] = {1776, 7, 4};
    third.assign(myints, myints + 3);  // assigning from array.

    std::cout << "Size of first: " << int(first.size()) << '\n';
    std::cout << "Size of second: " << int(second.size()) << '\n';
    std::cout << "Size of third: " << int(third.size()) << '\n';

    std::cout << "------------- MAIN -------------" << std::endl;
    return (0);
}
