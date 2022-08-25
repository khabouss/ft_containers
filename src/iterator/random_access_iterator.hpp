// Complete
#if !defined(SRC_ITERATOR_RANDOM_ACCESS_ITERATOR_HPP_)
#define SRC_ITERATOR_RANDOM_ACCESS_ITERATOR_HPP_

#include <iostream>
#include "iterator_traits.hpp"
#include "iterator.hpp"

namespace ft
{

    template <class T>
    class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
    {

    public:
        typedef iterator<ft::random_access_iterator_tag, T> iterator;
        typedef typename iterator::value_type               value_type;
        typedef typename iterator::difference_type          difference_type;
        typedef typename iterator::pointer                  pointer;
        typedef typename iterator::reference                reference;
        typedef typename iterator::iterator_category        iterator_category;

        random_access_iterator(void) : _ptr(NULL) {}
        explicit random_access_iterator(pointer ptr) : _ptr(ptr) {}
        ~random_access_iterator() {}
        random_access_iterator(const random_access_iterator &ptr) { this->_ptr = ptr.getPointer(); }

        pointer getPointer() const { return this->_ptr; }

        random_access_iterator  &operator++(void) { _ptr++; return *this; }
        random_access_iterator  &operator++(int) { random_access_iterator previous(*this); _ptr++; return previous; }
        bool                    &operator==(const random_access_iterator &rhs) const { return _ptr == rhs.getPointer(); }
        bool                    &operator!=(const random_access_iterator &rhs) const { return _ptr != rhs.getPointer(); }
        difference_type         &operator-(const random_access_iterator &rhs) const { return _ptr - rhs.getPointer(); }
        difference_type         &operator+(const random_access_iterator &rhs) const { return _ptr + rhs.getPointer(); }
        value_type              &operator[](size_t const & n) { return *(this->_ptr + n); }
        random_access_iterator  &operator+(const size_t n) { return random_access_iterator(_ptr + n); }
        random_access_iterator  &operator-(const size_t n) { return random_access_iterator(_ptr - n); }
        value_type              &operator*() { return *_ptr; }

    private:
        pointer _ptr;
    
    };

            template <typename T>
            typename ft::random_access_iterator<T>::difference_type
    operator-(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
            { return (lhs.getPointer() - rhs.getPointer()); }

            template <typename T>
            typename ft::random_access_iterator<T>::difference_type
    operator+(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
            { return (lhs.getPointer() + rhs.getPointer()); }

            template <typename T> bool
    operator<(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
            { return (lhs.getPointer() < rhs.getPointer()); }

            template <typename T> bool
    operator<=(const ft::random_access_iterator<T> lhs,
            const ft::random_access_iterator<T> rhs)
            { return (lhs.getPointer() <= rhs.getPointer()); }

            template <typename T> bool
    operator>(const ft::random_access_iterator<T> lhs,
            const ft::random_access_iterator<T> rhs)
            { return (lhs.getPointer() > rhs.getPointer()); }

            template <typename T> bool
    operator>=(const ft::random_access_iterator<T> lhs,
            const ft::random_access_iterator<T> rhs)
            { return (lhs.getPointer() >= rhs.getPointer()); }


            /* For iterator operator const_iterator */
            template <typename T_L, typename T_R>
            typename ft::random_access_iterator<T_L>::difference_type
    operator-(const ft::random_access_iterator<T_L> lhs,
            const ft::random_access_iterator<T_R> rhs)
            { return (lhs.getPointer() - rhs.getPointer()); }

            template <typename T_L, typename T_R>
            typename ft::random_access_iterator<T_L>::difference_type
    operator+(const ft::random_access_iterator<T_L> lhs,
            const ft::random_access_iterator<T_R> rhs)
            { return (lhs.getPointer() + rhs.getPointer()); }

            template <typename T_L, typename T_R>
            bool
    operator<(const ft::random_access_iterator<T_L> lhs,
            const ft::random_access_iterator<T_R> rhs)
            { return (lhs.getPointer() < rhs.getPointer()); }

            template <typename T_L, typename T_R>
            bool
    operator<=(const ft::random_access_iterator<T_L> lhs,
            const ft::random_access_iterator<T_R> rhs)
            { return (lhs.getPointer() <= rhs.getPointer()); }

            template <typename T_L, typename T_R>
            bool
    operator>(const ft::random_access_iterator<T_L> lhs,
            const ft::random_access_iterator<T_R> rhs)
            { return (lhs.getPointer() > rhs.getPointer()); }

            template <typename T_L, typename T_R>
            bool
    operator>=(const ft::random_access_iterator<T_L> lhs,
            const ft::random_access_iterator<T_R> rhs)
            { return (lhs.getPointer() >= rhs.getPointer()); }

} // namespace ft

#endif // SRC_ITERATOR_RANDOM_ACCESS_ITERATOR_HPP_
