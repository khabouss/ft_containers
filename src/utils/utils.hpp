// Copyright 2022 Taha Khabouss
#ifndef SRC_UTILS_UTILS_HPP_
#define SRC_UTILS_UTILS_HPP_

namespace ft
{

    // --------------------------------------------------------- is_integral ---------------------------------------------------------------------------
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

    // ------------------------------------------------------------------------------------------------------------------------------------

    template <class T>
	void swap(T &a, T &b)
	{
		T tmp(a);
		a = b;
		b = tmp;
	}

    template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
	{
		while (lit != lend)
		{
			if (rit == rend || *rit < *lit)
				return (false);
			else if (*lit < *rit)
				return (true);
			++lit, ++rit;
		}

		return (rit != rend);
	}

	template <class T>
	bool lexicographical_compare (T & a, T & b)
	{
		return (a < b);
	}

	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
	{
		while (lit != lend)
		{
			if (rit == rend || *rit != *lit)
				return (false);
			++lit, ++rit;
		}

		return (rit == rend);
	}

	template <class T>
	bool equal (T & a, T & b)
	{
		return (a == b);
	}


	template <bool B, class T = void>
	struct enable_if {};
	template <class T>
	struct enable_if<true, T> { typedef T type; };


	template <class T, class U>
	struct is_same { static const bool value = false; };
	template <class T>
	struct is_same<T, T> { static const bool value = true; };


	template <bool B, class T = void, class U = void>
	struct conditional {};
	template <class T, class U>
	struct conditional<true, T, U> { typedef T type; };
	template <class T, class U>
	struct conditional<false, T, U> { typedef U type; };

}  //  namespace ft

#endif //  SRC_UTILS_UTILS_HPP_