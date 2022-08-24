#if !defined(SRC_ITERATOR_REVERSE_ITERATOR_HPP_)
#define SRC_ITERATOR_REVERSE_ITERATOR_HPP_

#include "iterator_traits.hpp"

namespace ft
{

    template <class Iterator>
    class reverse_iterator
    {

    public:
        typedef Iterator iterator_type;
        typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename ft::iterator_traits<Iterator>::value_type value_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer pointer;
        typedef typename ft::iterator_traits<Iterator>::reference reference;

        reverse_iterator() : current() {}
        explicit reverse_iterator(iterator_type x) : current(x) {}
        template <class U>
        reverse_iterator(const reverse_iterator<U> &other) : current(other.base()) {}

        ~reverse_iterator() {}

        iterator_type base() const { return current; }

        template <class U>
        reverse_iterator &operator=(const reverse_iterator<U> &other);

        reference operator*() const { iterator_type tmp = current; return *--tmp; }
        pointer operator->() const { return &(operator*()); }
        reference operator[](difference_type n) const { return this->base()[-n - 1]; }
        reverse_iterator &operator++() { --current; return *this; }
        reverse_iterator &operator--() { ++current; return *this; }
        reverse_iterator operator++(int) { reverse_iterator tmp = *this; --current; return tmp; }
        reverse_iterator operator--(int) { reverse_iterator tmp = *this; ++current; return tmp; }
        reverse_iterator operator+(difference_type n) const { return reverse_iterator(current - n); }
        reverse_iterator operator-(difference_type n) const { return reverse_iterator(current + n); }
        reverse_iterator &operator+=(difference_type n) { operator+(n); return *this; }
        reverse_iterator &operator-=(difference_type n) { operator-(n); return *this; }

    protected:
        iterator_type current;
    };

    template <class Iterator1, class Iterator2>
    bool operator==(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs) { return lhs.base() == rhs.base(); }

    template <class Iterator1, class Iterator2>
    bool operator!=(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs) { return lhs.base() != rhs.base(); }

    template <class Iterator1, class Iterator2>
    bool operator<(const ft::reverse_iterator<Iterator1> &lhs,
                   const ft::reverse_iterator<Iterator2> &rhs) { return lhs.base() < rhs.base(); }

    template <class Iterator1, class Iterator2>
    bool operator<=(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs) { return lhs.base() <= rhs.base(); }

    template <class Iterator1, class Iterator2>
    bool operator>(const ft::reverse_iterator<Iterator1> &lhs,
                   const ft::reverse_iterator<Iterator2> &rhs) { return lhs.base() > rhs.base(); }

    template <class Iterator1, class Iterator2>
    bool operator>=(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs) { return lhs.base() >= rhs.base(); }

    template <class Iter>
    reverse_iterator<Iter>
    operator+(typename reverse_iterator<Iter>::difference_type n,
              const reverse_iterator<Iter> &it) {return reverse_iterator<Iter>(it.base() - n); }

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator> &lhs,
              const reverse_iterator<Iterator> &rhs) {return rhs.base() - lhs.base(); }

} // namespace ft

#endif // SRC_ITERATOR_REVERSE_ITERATOR_HPP_
