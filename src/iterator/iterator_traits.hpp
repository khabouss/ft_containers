#if !defined(SRC_ITERATOR_ITERATOR_TRAITS_HPP_)
#define SRC_ITERATOR_ITERATOR_TRAITS_HPP_

namespace ft
{
    class random_access_iterator_tag
    {
    };
    class bidirectional_iterator_tag
    {
    };
    class forward_iterator_tag
    {
    };
    class output_iterator_tag
    {
    };
    class input_iterator_tag
    {
    };
    
    template <class Iter>
    class iterator_traits
    {
        typedef typename Iter::value_type value_type;
        typedef typename Iter::difference_type difference_type;
        typedef typename Iter::pointer pointer;
        typedef typename Iter::reference reference;
        typedef typename Iter::iterator_category iterator_category;
    };

    template <class T>
    class iterator_traits<T *>
    {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef typename ft::random_access_iterator_tag iterator_category;
    };

    template <class T>
    class iterator_traits<const T *>
    {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;
        typedef typename ft::random_access_iterator_tag iterator_category;
    };



} // namespace ft

#endif // SRC_ITERATOR_ITERATOR_TRAITS_HPP_
