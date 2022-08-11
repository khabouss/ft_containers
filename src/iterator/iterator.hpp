// Copyright 2022 Taha Khabouss
#ifndef SRC_ITERATOR_ITERATOR_HPP_
#define SRC_ITERATOR_ITERATOR_HPP_

#include <iostream>

namespace ft {

template <class Category, class T, class Distance = ptrdiff_t
, class Pointer = T *, class Reference = T &>
class iterator {
 public:
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
    typedef Category iterator_category;

    iterator(void) : _ptr(NULL) {}
    explicit iterator(pointer ptr) : _ptr(ptr) {}
    ~iterator() {}
    iterator(const iterator & ptr) {
        this->_ptr = ptr.getPointer();
    }
    pointer getPointer() const {
        return this->_ptr;
    }
    iterator& operator++() {
        ++this->_ptr;
        return *this;
    }
    bool operator==(const iterator &rhs) const {
        return _ptr == rhs.getPointer();
    }
    bool operator!=(const iterator &rhs) const {
        return _ptr != rhs.getPointer();
    }
    difference_type operator-(const iterator &rhs) const {
        return _ptr - rhs.getPointer();
    }
    difference_type operator+(const iterator &rhs) const {
        return _ptr + rhs.getPointer();
    }
    iterator operator+(const size_t n) {
        return iterator(_ptr + n);
    }
    iterator operator-(const size_t n) {
        return iterator(_ptr - n);
    }
    value_type &operator*() { return *_ptr; }

 private:
    pointer _ptr;
};

struct random_access_iterator_tag{};
struct bidirectional_iterator_tag{};
struct forward_iterator_tag{};
struct output_iterator_tag {};
struct input_iterator_tag {};

}   // namespace ft

#endif  // SRC_ITERATOR_ITERATOR_HPP_
