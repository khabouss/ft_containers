// Copyright 2022 Taha Khabouss
#ifndef SRC_UTILS_UTILS_HPP_
#define SRC_UTILS_UTILS_HPP_

namespace ft {

/*
This template is designed to provide compile-time constants as types.
It is used by several parts of the standard library as the base class for trait types,
especially in their bool variant
*/
template <class T, T v>
struct integral_constant {
  static const T value = v;
};

/*
If B is true, std::enable_if has a public member typedef type, equal to T;
otherwise, there is no member typedef.
*/
template<bool B, typename T = void>
struct enable_if {};
template<typename T>
struct enable_if<true, T> { typedef T type; };

/*
If T and U name the same type (taking into account const/volatile qualifications),
provides the member constant value equal to true. Otherwise value is false.
*/

template<>
struct is_integral_type<bool> {
  typedef T type;
            static const bool value = is_integral;
}

template< class T >
struct is_integral : public is_integral_type<T> {};

template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (*first1 < *first2) return true;
        if (*first2 < *first1) return false;
    }
    return (first1 == last1) && (first2 != last2);
}

template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2,
                             Compare comp)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (comp(*first1, *first2)) return true;
        if (comp(*first2, *first1)) return false;
    }
    return (first1 == last1) && (first2 != last2);
}


}

} //  namespace ft

#endif //  SRC_UTILS_UTILS_HPP_