#include "main.hpp"
#include <vector>



int main()
{
    std::cout << "------------- MAIN -------------" << std::endl;

    ft::vector<std::string> myvector;

    // set some initial content:
    for (int i = 1; i < 10; i++)
        myvector.push_back(std::to_string(i));

    myvector.resize(5);

    std::cout << "myvector contains:";
    for (size_t i = 0; i < myvector.size(); i++)
        std::cout << " [" << myvector[i] << "]";
    std::cout << '\n';

    std::cout << "back() -> " << myvector.back() << std::endl;
    std::cout << "front() -> " << myvector.front() << std::endl;

    std::cout << "------------- MAIN -------------" << std::endl;
    return (0);
}