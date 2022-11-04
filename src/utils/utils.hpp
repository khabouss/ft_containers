// Copyright 2022 Taha Khabouss
#ifndef SRC_UTILS_UTILS_HPP_
#define SRC_UTILS_UTILS_HPP_

namespace ft
{

    // SRC = https://en.cppreference.com/w/cpp/types/enable_if

    /*
    This template is designed to provide compile-time constants as types.
    It is used by several parts of the standard library as the base class for trait types,
    especially in their bool variant
    */
    template <class T, T v>
    struct integral_constant
    {
        static const T value = v;
    };

    /*
    If B is true, std::enable_if has a public member typedef type, equal to T;
    otherwise, there is no member typedef.
    */
    template <bool B, typename T = void>
    struct enable_if
    {
    };
    template <typename T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    /*
    If T and U name the same type (taking into account const/volatile qualifications),
    provides the member constant value equal to true. Otherwise value is false.
    */

    template<bool is_integral, typename T>
    struct is_integral_res {
        typedef T type;
        static const bool value = is_integral;
    };

    template <typename>
    struct is_integral_type : public is_integral_res<false, bool> {};

    template <>
    struct is_integral_type<bool> : public is_integral_res<true, bool> {};

    template <>
    struct is_integral_type<char> : public is_integral_res<true, char> {};

    template <>
    struct is_integral_type<char16_t> : public is_integral_res<true, char16_t> {};

    template <>
    struct is_integral_type<char32_t> : public is_integral_res<true, char32_t> {};

    template <>
    struct is_integral_type<wchar_t> : public is_integral_res<true, wchar_t> {};

    template <>
    struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};

    template <>
    struct is_integral_type<short int> : public is_integral_res<true, short int> {};

    template <>
    struct is_integral_type<int> : public is_integral_res<true, int> {};

    template <>
    struct is_integral_type<long int> : public is_integral_res<true, long int> {};

    template <>
    struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};

    template <>
    struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};

    template <>
    struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};

    template <>
    struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};

    template <>
    struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};

    template <>
    struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};


    template <class T>
    struct is_integral : public is_integral_type<T>
    {
    };

    template <class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        return (first1 == last1) && (first2 != last2);
    };

    template <class InputIt1, class InputIt2, class Compare>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2,
                                 Compare comp)
    {
         
        for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
        {
            if (comp(*first1, *first2))
                return true;
            if (comp(*first2, *first1))
                return false;
        }
        return (first1 == last1) && (first2 != last2);
    };

    static class nullptr_t
    {
    public:
        template <class T>
        operator T *() const { return (0); }
        template <class C, class T>
        operator T C::*() const { return (0); }

    private:
        void operator&() const;
    } u_nullptr = {};

}  //  namespace ft

#endif //  SRC_UTILS_UTILS_HPP_