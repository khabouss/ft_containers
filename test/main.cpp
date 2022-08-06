#include "main.hpp"



int main()
{
    std::cout << "------------- MAIN -------------" << std::endl;
    ft::vector<int> v;


    v.push_back(12);
    v.push_back(1);
    v.push_back(152);

    v.pop_back();

    std::cout << v.at(2) << std::endl;


    std::cout << "------------- MAIN -------------" << std::endl;
    return (0);
}