// Copyright 2022 Taha Khabouss
#include <iostream>
#include <vector>
#include "../src/vector/vector.hpp"

int main() {
    std::cout << "------------- MAIN -------------" << std::endl;

    std::vector<std::string> list_of_cities;

    list_of_cities.push_back("Tokyo");
    list_of_cities.push_back("IDK");
    list_of_cities.push_back("London");
    list_of_cities.push_back("Paris");
    list_of_cities.push_back("Marrakech");

    list_of_cities.insert(list_of_cities.begin() + 2, "-> Tokyo");

    for (size_t i = 0; i < list_of_cities.size(); i++)
        std::cout << list_of_cities.at(i) << " " << std::endl;
    

    std::cout << "------------- MAIN -------------" << std::endl;
    return (0);
}
