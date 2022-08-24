// Copyright 2022 Taha Khabouss
#ifndef SRC_ITERATOR_ITERATOR_HPP_
#define SRC_ITERATOR_ITERATOR_HPP_

namespace ft
{

    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
    class iterator
    {
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
    };

} // namespace ft

#endif // SRC_ITERATOR_ITERATOR_HPP_
