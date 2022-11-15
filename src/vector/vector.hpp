// Copyright 2022 Taha Khabouss
#ifndef SRC_VECTOR_VECTOR_HPP_
#define SRC_VECTOR_VECTOR_HPP_

#include <iostream>
#include <memory>
#include <exception>
#include "../iterator/random_access_iterator.hpp"
#include "../utils/utils.hpp"
#include "../utils/headers.hpp"
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

   public:
      explicit vector(const allocator_type &alloc = std::allocator<T>()) : _alloc(alloc), _size(0), _capacity(0), _pointer(NULL) {}

      explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
          : _alloc(alloc), _size(n), _capacity(n), _pointer(NULL)
      {
         _pointer = _alloc.allocate(n);
         _capacity = n;
         _size = n;
         for (size_t i = 0; i < _size; i++)
            _alloc.construct(_pointer + i, val);
      }

      template <class InputIterator>
      vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
             typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type * = 0)
          : _alloc(alloc), _size(last - first), _capacity(last - first), _pointer(NULL)
      {
         _pointer = _alloc.allocate(last - first);
         for (size_t i = 0; i < _size; i++)
            _alloc.construct(_pointer + i, *(first + i));
      }

      vector(const vector &x) : _alloc(x._alloc), _size(x._size), _capacity(x._capacity), _pointer(NULL)
      {
         _pointer = _alloc.allocate(_capacity);
         for (size_t i = 0; i < x.size(); i++)
            _alloc.construct(_pointer + i, x[i]);
      }

      ~vector()
      {
         this->clear();
         _alloc.deallocate(_pointer,_capacity);
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
            reserve(_capacity * 2);
         }
         _alloc.construct(_pointer + _size, value);
         _size++;
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
            if (_capacity > 0)
            {
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
         {
            _alloc.construct(_pointer + _size, val);
            _size++;
         }
      }

      iterator insert(iterator position, const value_type &val)
      {
         size_type pos_len = &(*position) - _pointer;
         pointer _end = _pointer + _size;
         if (size_type(_capacity) >= this->size() + 1)
         {
            for (size_type i = 0; i < pos_len; i++)
               _alloc.construct(_end - i, *(_end - i - 1));
            _end++;
            _alloc.construct(&(*position), val);
            _size++;
         }
         else
         {
            pointer new_start = pointer();
            pointer new_end = pointer();
            pointer new_end_capacity = pointer();

            int next_capacity = (this->size() * 2 > 0) ? this->size() * 2 : 1;
            new_start = _alloc.allocate(next_capacity);
            new_end = new_start + this->size() + 1;
            new_end_capacity = new_start + next_capacity;

            for (size_type i = 0; i < pos_len; i++)
               _alloc.construct(new_start + i, *(_pointer + i));
            _alloc.construct(new_start + pos_len, val);
            for (size_type j = 0; j < this->size() - pos_len; j++)
               _alloc.construct(new_end - j - 1, *(_end - j - 1));

            for (size_type l = 0; l < this->size(); l++)
               _alloc.destroy(_pointer + l);
            if (_pointer)
               _alloc.deallocate(_pointer, this->capacity());

            _pointer = new_start;
            _size++;
            _capacity = next_capacity;
         }
         return (iterator(_pointer + pos_len));
      }

      void insert(iterator position, size_type n, const value_type &val)
      {
         size_type off = position - this->begin();

         if (_size + n > _capacity)
         {
            if (_size + n > _capacity * 2)
               this->reserve(_size + n);
            else if (_capacity > 0)
               this->reserve(_capacity * 2);
            else
               this->reserve(1);
         }
         for (size_type i = 0; i < n; i++)
            _alloc.construct(_pointer + _size + i, val);
         for (int i = _size - 1; i >= 0 && i >= (int)off; i--)
            _pointer[i + n] = _pointer[i];
         for (size_type i = off; i < off + n; i++)
            _pointer[i] = val;
         _size = _size + n;
      }

      template <class InputIterator>
      typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
      insert(iterator position, InputIterator first, InputIterator last)
      {
         size_type off = position - this->begin();
         size_type n = 0;
         for (InputIterator cpy = first; cpy != last && n <= this->max_size(); cpy++)
            n++;

         if (_size + n > _capacity)
         {
            if (_size + n > _capacity * 2)
               this->reserve(_size + n);
            else if (_capacity > 0)
               this->reserve(_capacity * 2);
            else
               this->reserve(1);
         }

         for (size_type i = 0; i < n; i++)
            _alloc.construct(_pointer + _size + i, *first);
         for (int i = _size - 1; i >= 0 && i >= (int)off; i--)
            _pointer[i + n] = _pointer[i];
         for (size_type i = off; i < off + n; i++)
            _pointer[i] = *first++;
         _size = _size + n;
      }

      iterator erase(iterator position)
      {
         size_type val = position - begin();

         _size -= 1;
         _alloc.destroy(&_pointer[val]);
         for (size_type i = val; i < _size; i++)
         {
            _alloc.construct(&_pointer[i], _pointer[i + 1]);
            _alloc.destroy(&_pointer[i + 1]);
         }
         return iterator(&_pointer[val]);
      }

      iterator erase(iterator first, iterator last)
      {
         size_type diff = last - first;

         while (first != end() - diff)
         {
            *first = first[diff];
            ++first;
         }
         while (first != end())
         {
            _alloc.destroy(&(*first));
            ++first;
         }
         _size -= diff;
         return last - diff;
      }

      vector &operator=(const vector &x)
      {
         if (this == &x)
            return (*this);

         for (size_type i = 0; i < _size; i++)
            _alloc.destroy(_pointer + i);

         if (x._size > _capacity)
         {
            _alloc.deallocate(_pointer, _capacity);
            _capacity = x._size;
            _pointer = _alloc.allocate(_capacity);
         }

         _size = x._size;
         for (size_type i = 0; i < _size; i++)
            _alloc.construct(_pointer + i, x[i]);

         return (*this);
      }

      void swap(vector &x)
      {
         ft::swap(_alloc, x._alloc);
         ft::swap(_size, x._size);
         ft::swap(_capacity, x._capacity);
         ft::swap(_pointer, x._pointer);
      }

      void clear()
      {
         for (size_t i = 0; i < _size; i++)
            _alloc.destroy(_pointer + i);
         _size = 0;
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
      x.swap(y);
   }

   template <class T, class Alloc>
   bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
   {
      if (lhs.size() != rhs.size())
         return false;
      typename ft::vector<T>::const_iterator first1 = lhs.begin();
      typename ft::vector<T>::const_iterator first2 = rhs.begin();
      while (first1 != lhs.end())
      {
         if (first2 == rhs.end() || *first1 != *first2)
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
   }

   template <class T, class Alloc>
   bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs < rhs) && !(lhs == rhs); }

   template <class T, class Alloc>
   bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return (lhs > rhs) || lhs == rhs; }

   template <class T, class Alloc>
   bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return (lhs < rhs) || lhs == rhs; }

   template <class T, class Alloc>
   bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs == rhs); }
} // namespace ft

#endif // SRC_VECTOR_VECTOR_HPP_
