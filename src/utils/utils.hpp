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
template<class T, class U>
struct is_same : integral_constant<bool, false> {};
template<class T>
struct is_same<T, T> : integral_constant<bool, true> {};

} //  namespace ft

#endif //  SRC_UTILS_UTILS_HPP_