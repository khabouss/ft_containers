#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft
{
	template <class IteratorType>
	class map_reverse_iterator
	{
	public:

		typedef typename IteratorType::value_type value_type;

		map_reverse_iterator() : _ptr(IteratorType()) {}

		map_reverse_iterator(value_type *ptr) : _ptr(IteratorType(ptr)) {}

		map_reverse_iterator(const IteratorType & other)
		{
			_ptr = other;
			--_ptr;
		}

		template <class Y> // const
		map_reverse_iterator(const map_reverse_iterator<Y> & other) : _ptr(other.getIteratorType()) {}

		~map_reverse_iterator() {}

		map_reverse_iterator &operator=(const map_reverse_iterator & other)
		{
			_ptr = other.getIteratorType();
			return (*this);
		}
		
		map_reverse_iterator &operator+=(int n)
		{
			_ptr -= n;
			return (*this);
		}

		map_reverse_iterator &operator-=(int n)
		{
			_ptr += n;
			return (*this);
		}

		map_reverse_iterator &operator++()
		{
			--_ptr;
			return (*this);
		}
		map_reverse_iterator &operator--()
		{
			++_ptr;
			return (*this);
		}
		map_reverse_iterator operator++(int)
		{
			map_reverse_iterator<IteratorType> other(*this);
			--_ptr;
			return (other);
		}
		map_reverse_iterator operator--(int)
		{
			map_reverse_iterator<IteratorType> other(*this);
			++_ptr;
			return (other);
		}

		IteratorType base() { return (++IteratorType(_ptr)); }
		
		IteratorType getIteratorType() const { return (_ptr); }

		map_reverse_iterator operator+(int n) const { return (_ptr - n + 1); }
		map_reverse_iterator operator-(int n) const { return (_ptr + n + 1); }
		std::ptrdiff_t operator-(const map_reverse_iterator & other) const { return (other.getIteratorType() - _ptr); }

		value_type & operator[](size_t n) const { return (*(_ptr - n)); }
		value_type & operator*() const { return (*_ptr); }
		value_type * operator->() const { return (&(*_ptr)); }

		template <class Y>
		bool operator==(const map_reverse_iterator<Y> & other) const { return (_ptr == other.getIteratorType()); }

		template <class Y>
		bool operator!=(const map_reverse_iterator<Y> & other) const { return (_ptr != other.getIteratorType()); }

		template <class Y>
		bool operator<(const map_reverse_iterator<Y> & other) const { return (_ptr > other.getIteratorType()); }

		template <class Y>
		bool operator>(const map_reverse_iterator<Y> & other) const { return (_ptr < other.getIteratorType()); }

		template <class Y>
		bool operator<=(const map_reverse_iterator<Y> & other) const { return (_ptr >= other.getIteratorType()); }

		template <class Y>
		bool operator>=(const map_reverse_iterator<Y> & other) const { return (_ptr <= other.getIteratorType()); }


		// rm

	private:
		IteratorType _ptr;
	};
}

#endif
