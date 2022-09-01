#include <iostream> // std::cout
#include <iterator> // std::iterator_traits
#include <typeinfo> // typeid
#include <vector>
#include <cstddef>
#include "../src/vector/vector.hpp"
#include <iterator>
#include <type_traits>


int main()
{
    ft::vector<int> v(10, 0);
    v.insert(v.begin() + 2, 5); 

    for (size_t i=0; i<v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;
    return 0;
}