#include "main.hpp"
#include <vector>



int main()
{
    std::cout << "------------- MAIN -------------" << std::endl;

    ft::vector<std::string> myvector;
    ft::vector<std::string> myvector2;

    myvector.push_back("1");
    myvector.push_back("2");
    myvector.push_back("3");
    myvector.push_back("4");
    myvector.push_back("5");
    myvector.push_back("6");
    myvector.push_back("7");

    //myvector2.assign(myvector.begin(), myvector.end());

    std::cout << "------------- MAIN -------------" << std::endl;
    return (0);
}