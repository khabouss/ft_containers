// Copyright 2022 Taha Khabouss
#ifndef SRC_VECTOR_VECTOR_HPP_
#define SRC_VECTOR_VECTOR_HPP_

#include <iostream>
#include <memory>
#include <exception>
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
      explicit vector(const allocator_type &alloc = std::allocator<T>()) : _alloc(alloc), _size(0), _capacity(0) { }

      explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
          : _alloc(alloc), _size(n), _capacity(n)
      {
         std::cout << "53 allocating " << n << " object" << std::endl;
         _pointer = _alloc.allocate(n);
         std::cout << "53 -- " << std::endl;
         _capacity = n;
         _size = n;
         for (size_t i = 0; i < _size; i++)
            _alloc.construct(_pointer + i, val);
      }

      template <class InputIterator>
      // dont use is_same
      vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
             typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type * = 0)
          : _alloc(alloc), _size(last - first), _capacity(last - first)
      {
         std::cout << "67 allocating " << (last - first) << " object" << std::endl;
         _pointer = _alloc.allocate(last - first);
         std::cout << "67 -- " << std::endl;
         for (size_t i = 0; i < _size; i++)
            _alloc.construct(_pointer + i, *(first + i));
      }

      vector(const vector &x) : _alloc(x._alloc), _size(x._size), _capacity(x._capacity)
      {
         std::cout << "75 allocating " << _capacity << " object" << std::endl;
         _pointer = _alloc.allocate(_capacity);
         std::cout << "75 -- " << std::endl;
         for (size_t i = 0; i < x.size(); i++)
            _alloc.construct(_pointer + i, x[i]);
      }

      ~vector()
      {
         this->clear();
         //_alloc.deallocate(_pointer, this->capacity()); <-- causes double free error
      }
      void push_back(const T &value)
      {
         if (_size == 0)
         {
            _capacity++;
            std::cout << "91 allocating " << _capacity << " object" << std::endl;
            _pointer = _alloc.allocate(_capacity);
            std::cout << "91 -- " << std::endl;
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
            std::cout << "124 allocating " << n << " object" << std::endl;
            pointer tmp = _alloc.allocate(n);
            std::cout << "124 -- " << std::endl;
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
         std::cout << "220 allocating " << _capacity << " object" << std::endl;
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
         std::cout << "238 allocating " << _capacity << " object" << std::endl;
         _pointer = _alloc.allocate(_capacity);
         for (size_t i = 0; i < n; i++)
            construct(val);
      }

      iterator __insert_(iterator position, const value_type &val, size_t fix)
      {
         size_t diff = (ft::distance(begin(), position));
         if (_capacity == _size && _capacity != 0)
            reserve(fix);
         else if (_capacity == 0)
         {
            push_back(val);
            return iterator(_pointer);
         }
         pointer tmp = _pointer + _size;
         while (_size >= diff)
         {
            _alloc.construct(tmp + 1, *(tmp));
            tmp--;
            diff++;
         }
         _alloc.construct(tmp + 1, val);
         _size++;
         return iterator(tmp + 1);
      }

      iterator insert(iterator position, const value_type &val)
      {
         size_t diff = (ft::distance(begin(), position));
         if (_capacity == _size && _capacity != 0)
            reserve(_capacity * 2);
         else if (_capacity == 0)
         {
            push_back(val);
            return iterator(_pointer);
         }
         pointer tmp = _pointer + _size;
         while (_size >= diff)
         {
            _alloc.construct(tmp + 1, *(tmp));
            tmp--;
            diff++;
         }
         _alloc.construct(tmp + 1, val);
         _size++;
         return iterator(tmp + 1);
      }

      void insert(iterator position, size_type n, const value_type &val)
      {
         size_t init_capacity = _capacity;
         for (size_t i = 0; i < n; i++)
         {
            position = __insert_(position, val, (n <= init_capacity) ? init_capacity * 2 : init_capacity + n);
         }
      }

      template <class InputIterator>
      typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
      insert(iterator position, InputIterator first, InputIterator last)
      {
         difference_type n = last - first - 1;
         difference_type init_capacity = _capacity;
         for (; n >= 0; n--)
            position = __insert_(position, *(first + n), (n <= init_capacity) ? init_capacity * 2 : (init_capacity) ? init_capacity + n + 1 : n + 2);
      }

      iterator erase (iterator position)
      {
         pointer pos = position.getPointer();
         pointer end = _pointer + _size;
         if (pos + 1 == end) // last element
            _alloc.destroy(pos);
         else
         {
            for (int i = 0; i < end - pos - 1; i++)
            {
               _alloc.construct(pos + i, *(pos + i + 1));
               _alloc.destroy(pos + i + 1);
            }
         }
         _size--;
         return (iterator(pos));
      }

      iterator erase(iterator first, iterator last)
      {
         difference_type diff = last - first;
         while (diff--)
            first = erase(first);
         return first;
      }
      vector &operator=(const vector &x)
      {
         if (x == *this)
					return *this;
         this->_alloc = x._alloc;
         this->_size = x._size;
         this->_capacity = x._capacity;
         this->_pointer = x._pointer;
         return *this;
      }

      void swap (vector& x)
		{
			if (x == *this)
				return;			
			std::size_t save_size = x._size;
			std::size_t save_capacity = x._capacity;
         pointer save_pointer = x._pointer;
			allocator_type save_alloc = x._alloc;
			x._pointer = this->_pointer;
			x._alloc = this->_alloc;
			this->_pointer = save_pointer;
			this->_alloc = save_alloc;
         this->_size = save_size;
         this->_capacity = save_capacity;
		}

      void clear()
      {
         for(size_t i=0; i<_size; i++)
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
