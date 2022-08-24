// Copyright 2022 Taha Khabouss
#include <iostream>
#include <vector>
#include "../src/vector/vector.hpp"

#define ns std

#define NOCONTENT false
template <typename T>
void printVectorInfo(T con, bool show = true)
{
    std::cout << "-------------------" << std::endl;
    std::cout << "size = " << con.size() << std::endl;
    std::cout << "capacity = " << con.capacity() << std::endl;
    std::cout << "content: " << std::endl;
    std::cout << "max_size = " << con.max_size() << std::endl;
    for (size_t i = 0; i < con.size() && show; i++)
        std::cout << "  " << i << ". [" << con.at(i) << "]" << std::endl;
    std::cout << "-------------------" << std::endl;
}

int main()
{
    ns::vector<int> foo(3, 100); // three ints with a value of 100
    ns::vector<int> bar(2, 200); // two ints with a value of 200

    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

    return (0);
}
