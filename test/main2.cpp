#include <iostream>     // std::cout
#include <iterator>     // std::iterator_traits
#include <typeinfo>     // typeid
#include <vector>
#include <cstddef>
#include "../src/vector/vector.hpp"
#include <iterator>
#include <type_traits>

int main() {
    std::vector<int> v(5, 10);
    // typename std::iterator_traits<ft::vector<int>::iterator>::reference traits;
    std::cout << std::is_convertible<ft::vector<int>::iterator::iterator_category, std::input_iterator_tag>::value << std::endl;
    return 0;
}