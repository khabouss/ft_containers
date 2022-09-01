#include <iostream> // std::cout
#include <iterator> // std::iterator_traits
#include <typeinfo> // typeid
#include <vector>
#include <cstddef>
#include "../src/vector/vector.hpp"
#include <iterator>
#include <type_traits>
#define Vector vector
#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))

int main()
{
    /*
     * strings to store the resutls
     */
    std::string str, ft_str;
    /*
     * var to store the size and the capacity
     */
    ft::Vector<std::string>::size_type s, ft_s;
    ft::Vector<std::string>::size_type c, ft_c;
    ft::Vector<std::string>::iterator ft_it;
    std::vector<std::string>::iterator it;
    /*
     * bool to store the comparison
     */
    bool cond = false;

    std::vector<std::string> v(20, "string");
    ft::Vector<std::string> ft_v(20, "string");

    it = v.insert(v.begin() + 10, "hello");
    ft_it = ft_v.insert(ft_v.begin() + 10, "hello");
    ft_it->length();

    str.clear();
    ft_str.clear();
    s = v.size();
    ft_s = ft_v.size();
    c = v.capacity();
    ft_c = ft_v.capacity();
    for (size_t i = 0; i < v.size(); ++i)
        str += v[i];
    for (size_t i = 0; i < ft_v.size(); ++i)
        ft_str += ft_v[i];
    cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it));
    EQUAL((c == ft_c));
    return 0;
}