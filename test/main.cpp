// Copyright 2022 Taha Khabouss
#include <iostream>
#include <vector>
#include "../src/vector/vector.hpp"


int main() {

    ft::vector<int> second (4,100);
    ft::vector<int> third (second.begin(),second.end());
    
    std::cout << "_size=" << third.size() << " _capacity=" << third.capacity() << std::endl;
    
    for (size_t i=0; i<third.size(); i++)
        std::cout << third.at(i) << ", ";
    return (0);
}
