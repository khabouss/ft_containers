// Copyright 2022 Taha Khabouss
#ifndef SRC_VECTOR_VECTOR_HPP_
#define SRC_VECTOR_VECTOR_HPP_

#include <iostream>
#include "../iterator/iterator.hpp"
#include <memory>

namespace ft {

template <class T, class Alloc = std::allocator<T> >
class vector {
 private:
   Alloc _alloc;
   std::size_t _size;
   std::size_t _capacity;
   std::size_t _max_size;
   typedef ft::iterator<ft::random_access_iterator_tag, T> iterator;
   typedef typename Alloc::pointer pointer;
   iterator _end;
   iterator _begin;
   pointer _pointer;
   typedef T value_type;
   typedef value_type &reference;
   typedef size_t size_type;
   typedef const value_type& const_reference;
   void construct(const T &value) {
      _alloc.construct(_pointer + _size, value);
      _size++;
   }

 public:
   explicit vector(const Alloc &alloc = std::allocator<T>()) : 
   _alloc(alloc), _size(0), _capacity(0), _end(NULL), _begin(NULL) {
      _max_size = _alloc.max_size();
   }
   ~vector() {
      std::cout << "Destructor is reached" << std::endl;
      //_alloc.deallocate(_pointer, _capacity);
      //_alloc.destroy(_pointer);
      //system(("leaks " + std::to_string(getpid())).c_str());
   }
   void push_back(const T &value) {
      if (_size == 0) {
         _capacity++;
         _pointer = _alloc.allocate(_capacity);
         
      }
      if (_size == _capacity) {
         _capacity *= 2;
         _alloc.allocate(_capacity);
         
      }
      construct(value);
   }

   void pop_back() {
      if (_capacity == 0)
         return;
      Alloc temp;
      pointer t = temp.allocate(_capacity);
      for (size_t i = 0; i < _size - 1; i++)
         temp.construct(t + i, *(_pointer + i));
      _alloc.deallocate(_pointer, _capacity);
      _alloc = temp;
      _pointer = t;
      _size--;
   }
   size_type max_size() const {
      return this->_max_size;
   }
   size_type capacity() const {
      return this->_capacity;
   }
   bool empty() const {
      return this->_size == 0;
   }
   void reserve (size_type n) {
      if (n > _capacity) {
         Alloc temp;
         pointer t = temp.allocate(n);
         for (size_t i = 0; i < _size; i++)
            temp.construct(t + i, *(_pointer + i));
         if (_capacity != 0)
            _alloc.deallocate(_pointer, _capacity);
         _alloc = temp;
         _pointer = t;
         _capacity = n;
      }
   }
   void resize (size_type n, value_type val = value_type()) {
      if (n < _size){
         for (size_t i = n; i < _size; i++)
            this->pop_back();
      }
      else {
         if (n >= _capacity)
            this->reserve(n);
         for (size_t i = _size; i < n; i++)
            _alloc.construct(_pointer+i, val);
      }
      _size = n;
   }
   iterator begin() {
      return iterator(this->_pointer);
   }
   iterator end() {
      return iterator(this->_pointer + _size);
   }
   size_type size() {
      return this->_size;
   }
   reference at(size_type n) {
      return (*(this->_pointer + n));
   }
   reference operator[] (size_type n) {
      return this->at(n);
   }
   const_reference operator[] (size_type n) const {
      return this->at(n);
   }
   reference front() {
      return this->at(0);
   }
   const_reference front() const {
      return this->at(0);
   }
   reference back() {
      return this->at(_size - 1);
   }
   const_reference back() const {
      return this->at(_size - 1);
   }
   template <class InputIterator>
   void assign (InputIterator first, InputIterator last) {
      if (_capacity != 0) {
         _alloc.deallocate(_pointer, _capacity);
         _size = 0;
      }
      size_t new_vector_size = last - first;
      if (new_vector_size >= _capacity)
         _capacity = new_vector_size;
      _pointer = _alloc.allocate(_capacity);
      for (size_t i = 0; i < new_vector_size; i++) {
         // _alloc.construct(_pointer + _size, *(first + i));
         std::cout << "Val: " << *(first + i) << std::endl;
         _size++;
      }
   }
   void assign (size_type n, const value_type& val) {
      if (_capacity != 0) {
         _alloc.deallocate(_pointer, _capacity);
         _size = 0;
      }
      if (n >= _capacity)
         _capacity = n;
      _pointer = _alloc.allocate(_capacity);
      for (size_t i = 0; i < n; i++)
         construct(val);
   }
   iterator insert (iterator position, const value_type& val) {
      Alloc tmp;
      pointer ptr;
      size_t new_capacity = _capacity;

         if (_size + 1 > _capacity)
            new_capacity = _size + 1;
         ptr = tmp.allocate(new_capacity);
         if (position == _begin) {
            tmp.construct(ptr, val);
            for (size_t i = 0; i < _size; i++)
               tmp.construct(ptr + 1 + i, _pointer + i);
         }
         else {
            size_t i = 0;
            while (_begin + i != position)
               tmp.construct(ptr + i, _pointer + i);
            tmp.construct(ptr + i, val);
            for (size_t j = i+1; j < _size; j++)
               tmp.construct(ptr + j, _pointer + j - 1);
         }
         _alloc.deallocate(_capacity);
         _alloc = tmp;
         _capacity = new_capacity;
         _size++;
         _pointer = ptr;
      }
};

}  // namespace ft

#endif  // SRC_VECTOR_VECTOR_HPP_
