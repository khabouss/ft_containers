// Copyright 2022 Taha Khabouss
#include <iostream>
#include <vector>
#include "../src/vector/vector.hpp"

using namespace ft;

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

int main ()
{
  std::vector<int> v;

  v.push_back(0);
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(5);
  v.push_back(6);
  v.push_back(7);
  v.push_back(8);
  v.push_back(9);
  v.push_back(10);
  v.push_back(11);
  v.push_back(12);
  v.push_back(13);

  
  std::vector<int>::iterator it = v.begin();
    
  std::cout << it[0] << std::endl; // 0
  std::cout << *it << std::endl; // 0
  it++;
  std::cout << *it << std::endl; // 1
  ++it;
  std::cout << *it << std::endl; // 2
  std::cout << (it == (it + 1)) << std::endl; // 0
  std::cout << (it != (it + 1)) << std::endl; // 1
  std::cout << it - (it++) << std::endl;


  return 0;
}