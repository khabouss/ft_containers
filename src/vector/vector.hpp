#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

namespace ft
{
   template <class T, class Alloc = std::allocator<T> >
   class vector
   {
   private:
      Alloc _alloc;
      std::size_t _size;
      std::size_t _capacity;
      std::size_t _maxSize;
      typedef typename std::iterator<std::random_access_iterator_tag, T> iterator;
      typedef typename Alloc::pointer pointer;
      iterator _end;
      iterator _begin;
      pointer _pointer;
      typedef T value_type;
      typedef value_type &reference;
      typedef size_t size_type;
      typedef const value_type& const_reference;

      void construct(const T &value)
      {
         _alloc.construct(_pointer + _size, value);
         _size++;
      }

   public:
      explicit vector(const Alloc &alloc = std::allocator<T>()) : _alloc(alloc), _size(0), _capacity(0), _maxSize(0) {

      }
      ~vector() {
         std::cout << "Destructor _pointer= " << *_pointer << std::endl;
         _alloc.deallocate(_pointer, _capacity);
         _alloc.destroy(_pointer);
         //system(("leaks " + std::to_string(getpid())).c_str());

      }

      void push_back(const T &value)
      {
         if (_size == 0)
         {
            _capacity++;
            _pointer = _alloc.allocate(_capacity);
            std::cout << "1 - capacity= " << _capacity << std::endl;
         }
         if (_size == _capacity)
         {
            _capacity *= 2;
            _alloc.allocate(_capacity);
            std::cout << "2 - _capacity= " << _capacity << std::endl;
         }
         construct(value);
      }

      iterator begin()
      {
         return iterator(this->_pointer);
      }

      iterator end()
      {
         return iterator(this->_pointer + _size);
      }

      size_type size()
      {
         return this->_size;
      }

      reference at(size_type n)
      {
         return (*(this->_pointer + n));
      }
   };

}

#endif