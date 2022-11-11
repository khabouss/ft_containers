#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
	//////////////////////////////
	// Reverse iterator
	//////////////////////////////

	template <class it>
	class map_reverse_iterator {
	public:
		// -structors
		map_reverse_iterator			(void)												{ _it = it(); }
		map_reverse_iterator			(typename it::value_type * ptr)						{ _it = it(ptr); }
		map_reverse_iterator			(const it & x)										{ _it = x; --_it; }
		~map_reverse_iterator			(void)												{}
		// Conversion
		template <class U>			friend class										map_reverse_iterator;
		template <class U>
		map_reverse_iterator			(const map_reverse_iterator<U> & x)						{ _it = x.getIt(); }

		// Assignment
		map_reverse_iterator &			operator=	(const map_reverse_iterator & x)			{ _it = x.getIt(); return (*this); }
		map_reverse_iterator &			operator+=	(int n)									{ _it -= n; return (*this); }
		map_reverse_iterator &			operator-=	(int n)									{ _it += n; return (*this); }
		// Comparison
		template <class U> bool		operator==	(const map_reverse_iterator<U> & x) const	{ return (_it == x.getIt()); }
		template <class U> bool		operator!=	(const map_reverse_iterator<U> & x) const	{ return (_it != x.getIt()); }
		template <class U> bool		operator<	(const map_reverse_iterator<U> & x) const	{ return (_it > x.getIt()); }
		template <class U> bool		operator>	(const map_reverse_iterator<U> & x) const	{ return (_it < x.getIt()); }
		template <class U> bool		operator<=	(const map_reverse_iterator<U> & x) const	{ return (_it >= x.getIt()); }
		template <class U> bool		operator>=	(const map_reverse_iterator<U> & x) const	{ return (_it <= x.getIt()); }
		// -crementation
		map_reverse_iterator &			operator++	(void)									{ --_it; return (*this); }
		map_reverse_iterator &			operator--	(void)									{ ++_it; return (*this); }
		map_reverse_iterator			operator++	(int)									{ map_reverse_iterator<it> x(*this); --_it; return (x); }
		map_reverse_iterator			operator--	(int)									{ map_reverse_iterator<it> x(*this); ++_it; return (x); }
		// Operation
		map_reverse_iterator			operator+	(int n) const							{ return (_it - n + 1); }
		map_reverse_iterator			operator-	(int n) const							{ return (_it + n + 1); }
		std::ptrdiff_t				operator-	(const map_reverse_iterator & x) const		{ return (x.getIt() - _it); }
		// Dereference
		typename it::value_type &	operator[]	(size_t n) const						{ return (*(_it - n)); }
		typename it::value_type &	operator*	(void) const							{ return (*_it); }
		typename it::value_type *	operator->	(void) const							{ return (&(*_it)); }
		// Member functions
		it							base		(void)									{ return (++it(_it)); }
		it							getIt		(void) const							{ return (_it); }
		// Non-member functions
		friend map_reverse_iterator		operator+	(int n, const map_reverse_iterator & x)		{ return (x.getIt() - n + 1); }

	private:
		it		_it;
	};
}

#endif
