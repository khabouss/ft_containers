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

        reverse_iterator();
        explicit reverse_iterator(iterator_type x);
        template <class U>
        reverse_iterator(const reverse_iterator<U> &other);

        template <class U>
        reverse_iterator &operator=(const reverse_iterator<U> &other);

        iterator_type base() const;

        reference operator*() const;
        pointer operator->() const;

        reference operator[](difference_type n) const;
        reverse_iterator &operator++();
        reverse_iterator &operator--();
        reverse_iterator operator++(int);
        reverse_iterator operator--(int);
        reverse_iterator operator+(difference_type n) const;
        reverse_iterator operator-(difference_type n) const;
        reverse_iterator &operator+=(difference_type n);
        reverse_iterator &operator-=(difference_type n);

    protected:
        iterator_type current;
    };

    template <class Iterator1, class Iterator2>
    bool operator==(const std::reverse_iterator<Iterator1> &lhs,
                    const std::reverse_iterator<Iterator2> &rhs);

    template <class Iterator1, class Iterator2>
    bool operator!=(const std::reverse_iterator<Iterator1> &lhs,
                    const std::reverse_iterator<Iterator2> &rhs);

    template <class Iterator1, class Iterator2>
    bool operator<(const std::reverse_iterator<Iterator1> &lhs,
                   const std::reverse_iterator<Iterator2> &rhs);

    template <class Iterator1, class Iterator2>
    bool operator<=(const std::reverse_iterator<Iterator1> &lhs,
                    const std::reverse_iterator<Iterator2> &rhs);

    template <class Iterator1, class Iterator2>
    bool operator>(const std::reverse_iterator<Iterator1> &lhs,
                   const std::reverse_iterator<Iterator2> &rhs);

    template <class Iterator1, class Iterator2>
    bool operator>=(const std::reverse_iterator<Iterator1> &lhs,
                    const std::reverse_iterator<Iterator2> &rhs);

    template <class Iter>
    reverse_iterator<Iter>
    operator+(typename reverse_iterator<Iter>::difference_type n,
              const reverse_iterator<Iter> &it);

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator> &lhs,
              const reverse_iterator<Iterator> &rhs);

} // namespace ft


#endif // SRC_ITERATOR_REVERSE_ITERATOR_HPP_
