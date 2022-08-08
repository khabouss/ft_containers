#ifndef ITERATOR
#define ITERATOR

#include <iostream>

namespace ft
{
    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
    class iterator
    {
    private:
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
        pointer _ptr;

    public:
        iterator(void) : _ptr(NULL) {}
        iterator(pointer ptr) : _ptr(ptr) {}
        ~iterator() {}
        iterator(const iterator & ptr) {
            this->_ptr = ptr.getPointer();
        }
        pointer getPointer() const {
            return this->_ptr;
        }
        iterator& operator++() {++this->_ptr;return *this;}
        bool operator==(const iterator &rhs) const { return _ptr == rhs.getPointer(); }
        bool operator!=(const iterator &rhs) const { return _ptr != rhs.getPointer(); }
        difference_type operator-(const iterator &rhs) const { return _ptr - rhs.getPointer(); }
        difference_type operator+(const iterator &rhs) const { return _ptr + rhs.getPointer(); }
      
        iterator operator+(const size_t n) { return iterator(_ptr + n); }
        iterator operator-(const size_t n) { return iterator(_ptr - n); }
        
        value_type &operator*() { return *_ptr; }
    };

    struct random_access_iterator_tag{};
    struct bidirectional_iterator_tag{};
    struct forward_iterator_tag{};
    struct output_iterator_tag {};
    struct input_iterator_tag {};
}

#endif