// Complete
#if !defined(SRC_ITERATOR_RANDOM_ACCESS_ITERATOR_HPP_)
#define SRC_ITERATOR_RANDOM_ACCESS_ITERATOR_HPP_

#include <iostream>

#include "iterator.hpp"

namespace ft
{

    struct input_iterator_tag {};
    ///  Marking output iterators.
    struct output_iterator_tag {};
    /// Forward iterators support a superset of input iterator operations.
    struct forward_iterator_tag : public input_iterator_tag {};
    /// Bidirectional iterators support a superset of forward iterator
    /// operations.
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    /// Random-access iterators support a superset of bidirectional iterator
    /// operations.
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};
    
    template <class Iter>
    class iterator_traits
    {
    public:
        typedef typename Iter::value_type value_type;
        typedef typename Iter::difference_type difference_type;
        typedef typename Iter::pointer pointer;
        typedef typename Iter::reference reference;
        typedef typename Iter::iterator_category iterator_category;
    };

    template <class T>
    class iterator_traits<T *>
    {
    public:
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef typename ft::random_access_iterator_tag iterator_category;
    };

    template <class T>
    class iterator_traits<const T *>
    {
    public:
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;
        typedef typename ft::random_access_iterator_tag iterator_category;
    };
    
    template <class T>
    class random_access_iterator
    {

    public:
        typedef iterator<ft::random_access_iterator_tag, T> iterator;
        typedef typename iterator::value_type               value_type;
        typedef typename iterator::difference_type          difference_type;
        typedef typename iterator::pointer                  pointer;
        typedef typename iterator::reference                reference;
        typedef typename iterator::iterator_category        iterator_category;

        random_access_iterator(void) : _ptr(NULL) {};
        explicit random_access_iterator(pointer ptr) : _ptr(ptr) {};
        ~random_access_iterator() {};
        template<class L>
        random_access_iterator(random_access_iterator<L> const &ptr) { this->_ptr = ptr.getPointer(); };

        pointer getPointer() const { return this->_ptr; };

        random_access_iterator  operator=(const random_access_iterator & other) { this->_ptr = other.getPointer(); return *this; };
        random_access_iterator  operator++(void) { _ptr++; return *this; }
        random_access_iterator  operator--(void) { _ptr--; return *this; }
        random_access_iterator  operator++(int) { random_access_iterator previous(*this); _ptr++; return previous; }
        random_access_iterator  operator--(int) { random_access_iterator previous(*this); _ptr--; return previous; }
        bool                    operator==(const random_access_iterator &rhs) const { return _ptr == rhs.getPointer(); }
        bool                    operator!=(const random_access_iterator &rhs) const { return _ptr != rhs.getPointer(); }
        difference_type         operator-(const random_access_iterator &rhs) const { return _ptr - rhs.getPointer(); }
        difference_type         operator+(const random_access_iterator &rhs) const { return _ptr + rhs.getPointer(); }
        random_access_iterator  operator+=(const difference_type & n) { _ptr += n; return *this; }
        random_access_iterator  operator-=(const difference_type & n) { _ptr -= n; return *this; }
        value_type              &operator[](size_t const & n) { return *(this->_ptr + n); }
        random_access_iterator  operator+(const difference_type n) { return random_access_iterator(_ptr + n); }
        random_access_iterator  operator-(const difference_type n) { return random_access_iterator(_ptr - n); }
        reference               operator*() { return *_ptr; }
        pointer                 operator->() { return _ptr; }

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

    // with int
            template <typename T>
            typename ft::random_access_iterator<T>::pointer
    operator+(typename ft::random_access_iterator<T>::difference_type lhs,
            const ft::random_access_iterator<T> rhs)
            { return (lhs + rhs.getPointer()); }

            template <typename T>
            typename ft::random_access_iterator<T>::pointer
    operator+(const ft::random_access_iterator<T> rhs,
                typename ft::random_access_iterator<T>::difference_type lhs)
            { return (lhs + rhs.getPointer()); }

            template <typename T>
            typename ft::random_access_iterator<T>::pointer
    operator-(typename ft::random_access_iterator<T>::difference_type lhs,
            const ft::random_access_iterator<T> rhs)
            { return (lhs - rhs.getPointer()); }

            template <typename T>
            typename ft::random_access_iterator<T>::pointer
    operator-(const ft::random_access_iterator<T> rhs,
                typename ft::random_access_iterator<T>::difference_type lhs)
            { return (rhs.getPointer() - lhs); }

} // namespace ft

#endif // SRC_ITERATOR_RANDOM_ACCESS_ITERATOR_HPP_
