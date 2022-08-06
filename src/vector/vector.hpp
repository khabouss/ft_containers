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
      std::size_t _max_size;
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
         _max_size = _alloc.max_size();
      }
      ~vector() {
         std::cout << "Destructor _pointer= " << *_pointer << std::endl;
         //_alloc.deallocate(_pointer, _capacity);
         //_alloc.destroy(_pointer);
         //system(("leaks " + std::to_string(getpid())).c_str());

      }

      void push_back(const T &value)
      {
         if (_size == 0)
         {
            _capacity++;
            _pointer = _alloc.allocate(_capacity);
            
         }
         if (_size == _capacity)
         {
            _capacity *= 2;
            _alloc.allocate(_capacity);
            
         }
         construct(value);
      }

      void pop_back() {
         Alloc temp;
         pointer t = temp.allocate(_capacity);
         for (size_t i=0; i < _size - 1; i++)
            temp.construct(t + i, *(_pointer + i));
         _alloc.deallocate(_pointer, _capacity);
         _alloc = temp;
         _pointer = t;
         _size--;
      }

      size_type max_size() const {
         return this->_max_size;
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