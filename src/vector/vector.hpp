// Copyright 2022 Taha Khabouss
#ifndef SRC_VECTOR_VECTOR_HPP_
#define SRC_VECTOR_VECTOR_HPP_

#include <iostream>
#include <memory>
#include "../iterator/random_access_iterator.hpp"
#include "../utils/utils.hpp"
#include "../iterator/reverse_iterator.hpp"

namespace ft
{

   template <class T, class Alloc = std::allocator<T> >
   class vector
   {

   public:
      typedef T value_type;
      typedef Alloc allocator_type;
      typedef typename allocator_type::reference reference;
      typedef typename allocator_type::const_reference const_reference;
      typedef typename Alloc::pointer pointer;
      typedef typename Alloc::const_pointer const_pointer;
      typedef typename ft::random_access_iterator<T> iterator;
      typedef typename ft::random_access_iterator<const T> const_iterator;
      typedef typename ft::reverse_iterator<iterator> reverse_iterator;
      typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
      typedef ptrdiff_t difference_type;
      typedef size_t size_type;

   private:
      Alloc _alloc;
      std::size_t _size;
      std::size_t _capacity;
      pointer _pointer;
   

      void construct(const T &value)
      {
         _alloc.construct(_pointer + _size, value);
         _size++;
      }

   public:
      explicit vector(const allocator_type &alloc = std::allocator<T>()) : _alloc(alloc), _size(0), _capacity(0) {}

      explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
          : _alloc(alloc), _size(n), _capacity(n)
      {
         _pointer = _alloc.allocate(n);
         for (size_t i = 0; i < _size; i++)
            _alloc.construct(_pointer + i, val);
      }

      template <class InputIterator>
      // dont use is_same
      vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
             typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type * = 0)
          : _alloc(alloc), _size(last - first), _capacity(last - first)
      {
         _pointer = _alloc.allocate(last - first);
         for (size_t i = 0; i < _size; i++)
            _alloc.construct(_pointer + i, *(first + i));
      }

      vector(const vector &x)
      {
         _alloc = x._alloc;
         _size = x._size;
         _capacity = x._capacity;
         _pointer = x._pointer;
      }

      ~vector()
      {
         // _alloc.deallocate(_pointer, _capacity);
         // _alloc.destroy(_pointer);
         // system(("leaks " + std::to_string(getpid())).c_str());
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
            reserve(_capacity*2);
         }
         construct(value);
      }

      void pop_back()
      {
         _alloc.destroy(&this->back());
         _size--;
      }
      size_type max_size() const
      {
         return this->_alloc.max_size();
      }
      size_type capacity() const
      {
         return this->_capacity;
      }
      bool empty() const
      {
         return this->_size == 0;
      }
      void reserve(size_type n)
      {
         if (n > this->max_size())
            throw(std::length_error("vector::reserve"));
         else if (n > _capacity)
         {
            pointer tmp = _alloc.allocate(n);
            if (_capacity > 0){
               for (size_type i = 0; i < _size; i++)
                  _alloc.construct(tmp + i, *(_pointer + i));
               _alloc.deallocate(_pointer, _capacity);
            }
            _pointer = tmp;
            _capacity = n;
         }
      }
      void resize(size_type n, value_type val = value_type())
      {
         if (n < _size)
         {
            for (size_t i = n; i < _size; i++)
               this->pop_back();
         }
         else
         {
            if (n >= _capacity)
               this->reserve(n);
            for (size_t i = _size; i < n; i++)
               _alloc.construct(_pointer + i, val);
         }
         _size = n;
      }
      iterator begin()
      {
         return iterator(this->_pointer);
      }
      const_iterator begin() const
      {
         return const_iterator(this->_pointer);
      }
      iterator end()
      {
         return iterator(this->_pointer + _size);
      }
      const_iterator end() const
      {
         return const_iterator(this->_pointer + _size);
      }
      size_type size() const
      {
         return this->_size;
      }

      reference at(size_type n)
      {
         if (n > size())
            throw std::out_of_range("vector");
         return (*(this->_pointer + n));
      }
      const_reference at(size_type n) const
      {
         if (n > size())
            throw std::out_of_range("vector");
         return (*(this->_pointer + n));
      }
      reference operator[](size_type n)
      {
         return (*(_pointer + n));
      }
      const_reference operator[](size_type n) const
      {
         return (*(_pointer + n));
      }
      reference front()
      {
         return (*(this->_pointer));
      }
      const_reference front() const
      {
         return (*(this->_pointer));
      }
      reference back() 
      {
         return (*(this->_pointer + _size - 1));
      }
      const_reference back() const
      {
         return (*(this->_pointer + _size - 1));
      }

      template <class InputIterator>
      typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type assign(InputIterator first, InputIterator last)
      {
         if (_capacity != 0)
         {
            _alloc.deallocate(_pointer, _capacity);
            _size = 0;
         }
         size_t new_vector_size = last - first;
         if (new_vector_size >= _capacity)
            _capacity = new_vector_size;
         _pointer = _alloc.allocate(_capacity);
         for (size_t i = 0; i < new_vector_size; i++)
         {
            _alloc.construct(_pointer + _size, *(first + i));
            _size++;
         }
      }

      void assign(size_type n, const value_type &val)
      {
         if (_capacity != 0)
         {
            _alloc.deallocate(_pointer, _capacity);
            _size = 0;
         }
         if (n >= _capacity)
            _capacity = n;
         _pointer = _alloc.allocate(_capacity);
         for (size_t i = 0; i < n; i++)
            construct(val);
      }

      iterator insert(iterator position, const value_type &val)
      {
         size_t diff = position - iterator(_pointer); // c

         if (diff < 0)
            std::cout << "double free or corruption (out)" << std::endl; // throw exception or ...

         if (_size == _capacity)
         {
            _capacity++;
            _alloc.allocate(_capacity);
         }

         if (diff <= _size)
         {
            pointer tmp = _pointer + _size;
            while (_size >= diff)
            {
               // std::cout << "value: " << *tmp << std::endl;
               _alloc.construct(tmp + 1, *(tmp));
               tmp--;
               diff++;
            }
            _alloc.construct(tmp + 1, val);
            _size++;
            return position;
         }
         return iterator(this->_pointer);
      }

      void insert(iterator position, size_type n, const value_type &val)
      {
         for (size_t i = 0; i < n; i++)
            insert(position, val);
      }

      template <class InputIterator>
      typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
      insert(iterator position, InputIterator first, InputIterator last)
      {
         difference_type n = last - first - 1;
         for (; n >= 0; n--)
            insert(position, *(first + n));
      }

      iterator erase(iterator position)
      {
         // move all elements to new arr except for the one at position
         _size--;
         size_t old_capacity = _capacity;
         _capacity = _size;
         pointer tmp = _alloc.allocate(_capacity);
         size_t j = 0;
         size_t changed;
         for (size_t i = 0; i < _size; i++)
         {
            if (_pointer + i == position.getPointer())
               changed = (j++);
            _alloc.construct(tmp + i, *(_pointer + j));
            j++;
         }
         // maybe free old memory
         _alloc.deallocate(_pointer, old_capacity);
         _pointer = tmp;
         return iterator(_pointer + changed);
      }

      iterator erase(iterator first, iterator last)
      {
         difference_type diff = last - first;
         while (diff--)
            first = erase(first);
         return first;
      }
      void operator=(const vector &x)
      {
         this->_alloc = x._alloc;
         this->_size = x._size;
         this->_capacity = x._capacity;
         this->_pointer = x._pointer;
      }
      void swap(vector &x)
      {
         vector c(*this);
         *this = x;
         x = c;
      }
      void clear()
      {
         if (_size != 0)
            _alloc.deallocate(_pointer, _capacity);
         _size = 0;
         _capacity = 0;
      }

      allocator_type get_allocator() const
      {
         return _alloc;
      }
      reverse_iterator rbegin() { return reverse_iterator(iterator(_pointer + _size)); }
      const_reverse_iterator rbegin() const { return reverse_iterator(iterator(_pointer + _size)); }
      reverse_iterator rend() { return reverse_iterator(iterator(_pointer)); }
      const_reverse_iterator rend() const { return reverse_iterator(iterator(_pointer)); }
   };

   template <class T, class Alloc>
   void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
   {
      vector<T, Alloc> c(x);
      x = y;
      y = c;
   }

   template <class T, class Alloc>
   bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
   {
      typename vector<T, Alloc>::const_iterator first1 = lhs.begin();
      typename vector<T, Alloc>::const_iterator last1 = lhs.end();
      typename vector<T, Alloc>::const_iterator first2 = rhs.begin();
      typename vector<T, Alloc>::const_iterator last2 = rhs.end();

      while (first1 != last1)
      {
         if (!(*first1 == *first2))
            return false;
         ++first1;
         ++first2;
      }
      return true;
   }

   template <class T, class Alloc>
   bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
   {
      typename vector<T, Alloc>::const_iterator first1 = lhs.begin();
      typename vector<T, Alloc>::const_iterator last1 = lhs.end();
      typename vector<T, Alloc>::const_iterator first2 = rhs.begin();
      typename vector<T, Alloc>::const_iterator last2 = rhs.end();

      return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
      ;
   }

   template <class T, class Alloc>
   bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs < rhs); }

   template <class T, class Alloc>
   bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs < rhs) || lhs == rhs; }

   template <class T, class Alloc>
   bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return (lhs < rhs) || lhs == rhs; }

   template <class T, class Alloc>
   bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs == rhs); }
} // namespace ft

#endif // SRC_VECTOR_VECTOR_HPP_
