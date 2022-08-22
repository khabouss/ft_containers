// Copyright 2022 Taha Khabouss
#include <iostream>
#include <vector>
#include "../src/vector/vector.hpp"

#define ns std
#define NOCONTENT false

template <typename T>
void printVectorInfo(T con, bool show = true)
{
    std::cout << "-------------------" <<std::endl;
    std::cout << "size = " << con.size() << std::endl;
    std::cout << "capacity = " << con.capacity() << std::endl;
    std::cout << "content: " << std::endl;
    std::cout << "max_size = " << con.max_size() << std::endl;
    for (size_t i = 0; i < con.size() && show; i++)
        std::cout << "  " << i << ". [" << con.at(i) << "]" << std::endl;
    std::cout << "-------------------" << std::endl;
}

int main() {

    std::vector<int> foo(3, 100); // three ints with a value of 100
    std::vector<int> bar(5, 200); // five ints with a value of 200

    foo.swap(bar);

    std::cout << "foo contains:";
    for (std::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    std::cout << "bar contains:";
    for (std::vector<int>::iterator it = bar.begin(); it != bar.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return (0);
}
