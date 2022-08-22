// Copyright 2022 Taha Khabouss
#ifndef SRC_VECTOR_VECTOR_HPP_
#define SRC_VECTOR_VECTOR_HPP_

#include <iostream>
#include <memory>
#include "../iterator/iterator.hpp"
#include "../utils/utils.hpp"

namespace ft
{

   template <class T, class Alloc = std::allocator<T> >
   class vector
   {

   public:
      typedef Alloc allocator_type;
      typedef ft::iterator<ft::random_access_iterator_tag, T> iterator;
      typedef typename Alloc::pointer pointer;
      typedef T value_type;
      typedef value_type &reference;
      typedef size_t size_type;
      typedef const value_type &const_reference;
      typedef ptrdiff_t difference_type;

   private:
      Alloc _alloc;
      std::size_t _size;
      std::size_t _capacity;
      std::size_t _max_size;
      iterator _end;
      iterator _begin;
      pointer _pointer;

      void construct(const T &value)
      {
         _alloc.construct(_pointer + _size, value);
         _size++;
         _end = iterator(_pointer + _size);
      }

   public:
      explicit vector(const allocator_type &alloc = std::allocator<T>()) : _alloc(alloc), _size(0), _capacity(0), _end(NULL), _begin(NULL)
      {
         _max_size = _alloc.max_size();
      }

      explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
          : _alloc(alloc), _size(n), _capacity(n), _end(NULL), _begin(NULL)
      {
         _pointer = _alloc.allocate(n);
         for (size_t i = 0; i < _size; i++)
            _alloc.construct(_pointer + i, val);
         _begin = iterator(_pointer);
         _end = iterator(_pointer + _size);
         _max_size = _alloc.max_size();
      }

      template <class InputIterator>
      // dont use is_same
      vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename ft::enable_if<ft::is_same<InputIterator, iterator>::value, void>::type * = 0)
          : _alloc(alloc), _size(last - first), _capacity(last - first), _end(NULL), _begin(NULL)
      {
         _pointer = _alloc.allocate(last - first);
         for (size_t i = 0; i < _size; i++)
            _alloc.construct(_pointer + i, *(first + i));
         _begin = iterator(_pointer);
         _end = iterator(_pointer + _size);
         _max_size = _alloc.max_size();
      }

      vector(const vector &x)
      {
         _alloc = x._alloc;
         _size = x._size;
         _capacity = x._capacity;
         _max_size = x._max_size;
         _end = x._end;
         _begin = x._begin;
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
            _begin = iterator(_pointer);
            _end = iterator(_pointer + 1);
         }
         if (_size == _capacity)
         {
            _capacity++;
            _alloc.allocate(_capacity);
         }
         construct(value);
      }

      void pop_back()
      {
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
      size_type max_size() const
      {
         return this->_max_size;
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
         if (n > _capacity)
         {
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
      reference operator[](size_type n)
      {
         return this->at(n);
      }
      const_reference operator[](size_type n) const
      {
         return this->at(n);
      }
      reference front()
      {
         return this->at(0);
      }
      const_reference front() const
      {
         return this->at(0);
      }
      reference back()
      {
         return this->at(_size - 1);
      }
      const_reference back() const
      {
         return this->at(_size - 1);
      }

      template <class InputIterator>
      typename ft::enable_if<ft::is_same<InputIterator, iterator>::value, void>::type // dont use is_same
      assign(InputIterator first, InputIterator last)
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
         size_t diff = position - _begin;

         if (diff < 0 || diff > _capacity)
            std::cout << "Error in insert diff=" << diff << std::endl; // throw exception or ...

         if (_size == _capacity)
         {
            _capacity++;
            _alloc.allocate(_capacity);
         }

         if (diff <= _size)
         {
            pointer tmp = _end.getPointer();
            while (_size >= diff)
            {
               // std::cout << "value: " << *tmp << std::endl;
               _alloc.construct(tmp + 1, *(tmp));
               tmp--;
               diff++;
            }
            _alloc.construct(tmp + 1, val);
            _size++;
            ++_end;
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
      typename ft::enable_if<ft::is_same<InputIterator, iterator>::value, void>::type // dont use is_same
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
         _alloc.deallocate(_pointer, _capacity + 1);
         _pointer = tmp;
         _begin = begin();
         _end = end();
         return iterator(tmp + changed);
      }

      iterator erase(iterator first, iterator last)
      {
         difference_type diff = last - first;
         while (diff--)
            first = erase(first);
         return first;
      }

      void operator = (const vector &x)
      {
         this->_alloc = x._alloc;
         this->_size = x._size;
         this->_capacity = x._capacity;
         this->_max_size = x._max_size;
         this->_end = x._end;
         this->_begin = x._begin;
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
         if(_size != 0)
            _alloc.deallocate(_pointer, _capacity);
         _size = 0;
         _capacity = 0;
      }

      allocator_type get_allocator() const
      {
         return _alloc;
      }
   };

   

} // namespace ft

#endif // SRC_VECTOR_VECTOR_HPP_
