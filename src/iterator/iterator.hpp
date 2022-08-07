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
        iterator(pointer ptr) : _ptr(ptr) {}
        ~iterator() {}
    };

    struct random_access_iterator_tag{};
    struct bidirectional_iterator_tag{};
    struct forward_iterator_tag{};
    struct output_iterator_tag {};
    struct input_iterator_tag {};
}

#endif