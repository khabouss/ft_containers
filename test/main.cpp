// Copyright 2022 Taha Khabouss
#include <iostream>
#include <vector>
#include "../src/vector/vector.hpp"

#define ns ft

template <typename T>
void printVectorInfo(T con)
{
    std::cout << "-------------------" <<std::endl;
    std::cout << "size = " << con.size() << std::endl;
    std::cout << "capacity = " << con.capacity() << std::endl;
    std::cout << "content: " << std::endl;
    for (size_t i = 0; i < con.size(); i++)
        std::cout << "  " << i << ". [" << con.at(i) << "]" << std::endl;
    std::cout << "-------------------" << std::endl;
}

int main() {

    ns::vector<int> con;

    con.push_back(1);
    con.push_back(2);
    con.push_back(3);
    con.push_back(4);
    con.push_back(5);
    con.push_back(6);
    con.push_back(7);
    con.push_back(8);
    con.push_back(9);

    ns::vector<int>::iterator it = con.begin() + 2;
    con.insert(it, 0);

    printVectorInfo(con);

    return (0);
}
