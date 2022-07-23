#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>

namespace ft
{
   template <class T, class Alloc = std::allocator<T> > 
   class vector
   {
   private:
    Alloc _alloc;

   public:
    explicit vector(const Alloc & alloc = std::allocator<T>()) : _alloc(alloc) {}
    ~vector() {}
   };
   

}

#endif