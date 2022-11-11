#if !defined(MAP_ITERATOR)
#define MAP_ITERATOR

#include <iostream>
#include "../map/includes/containers.hpp"
#include "iterator.hpp"

#define _ITERATOR ft::iterator<std::bidirectional_iterator_tag, T> // <--

namespace ft
{
	template <class node, class Key, class T>
	class mapIterator : ft::iterator<std::bidirectional_iterator_tag, T>
	{

	public:
		typedef T *pointer;
		typedef T &reference;
		typedef typename _ITERATOR::iterator_category iterator_category;
		typedef ft::pair<const Key, T> pair_type;
		typedef typename ft::conditional<false, const pair_type, pair_type>::type value_type;
		typedef typename ft::conditional<false, const node, node>::type node_type;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

		mapIterator() : _ptr(NULL) {}
		mapIterator(node_type * const ptr) : _ptr(ptr) {}
		~mapIterator() {}

		mapIterator(const mapIterator<node, Key, T> &x) { _ptr = x.getPtr(); }

		mapIterator &operator=(const mapIterator &x) {
			_ptr = x.getPtr();
			return (*this);
		}

		bool operator==(const mapIterator<node, Key, T> &x) const { return (_ptr == x.getPtr()); }

		bool operator!=(const mapIterator<node, Key, T> &x) const { return (_ptr != x.getPtr()); }

		mapIterator& operator++()
		{
			if (_ptr->right != _ptr->right->left)
			{
				_ptr = _ptr->right;
				while (_ptr->left != _ptr->left->left)
					_ptr = _ptr->left;
			}
			else
			{
				while (_ptr == _ptr->parent->right && _ptr != _ptr->parent)
					_ptr = _ptr->parent;
				_ptr = _ptr->parent;
			}
			return (*this);
		}

		mapIterator& operator--()
		{
			if (_ptr == _ptr->parent) {
				while (_ptr->right != _ptr->right->left) {
					_ptr = _ptr->right;
				}
			}
			else if (_ptr->left != _ptr->left->left) {
				_ptr = _ptr->left;
				while (_ptr->right != _ptr->right->left) {
					_ptr = _ptr->right;
				}
			}
			else {
				while (_ptr == _ptr->parent->left && _ptr != _ptr->parent){
					_ptr = _ptr->parent;
				}
				_ptr = _ptr->parent;
			}
			return (*this);
		}

		mapIterator operator++(int)
		{
			mapIterator<node, Key, T> x(*this);
			this->operator++();
			return (x);
		}

		mapIterator operator--(int)
		{
			mapIterator<node, Key, T> x(*this);
			this->operator--();
			return (x);
		}

		node_type* getPtr() const { return (_ptr); }

		value_type& operator*() const { return (_ptr->data); }
		value_type* operator->() const { return (&_ptr->data); }

	private:
		node_type *_ptr;

	};


	// const map iterator
	template <class node, class Key, class T>
	class mapConstIterator : ft::iterator<std::bidirectional_iterator_tag, T>
	{

	public:
		typedef T *pointer;
		typedef T &reference;
		typedef typename _ITERATOR::iterator_category iterator_category;
		typedef ft::pair<const Key, T> pair_type;
		typedef typename ft::conditional<true, const pair_type, pair_type>::type value_type;
		typedef typename ft::conditional<true, const node, node>::type node_type;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

		mapConstIterator() : _ptr(NULL) {}
		mapConstIterator(node_type * const ptr) : _ptr(ptr) {}
		~mapConstIterator() {}

		mapConstIterator(const mapIterator<node, Key, T> &x) { _ptr = x.getPtr(); }

		mapConstIterator &operator=(const mapConstIterator &x) {
			_ptr = x.getPtr();
			return (*this);
		}

		bool operator==(const mapConstIterator<node, Key, T> &x) const { return (_ptr == x.getPtr()); }

		bool operator!=(const mapConstIterator<node, Key, T> &x) const { return (_ptr != x.getPtr()); }

		mapConstIterator& operator++()
		{
			if (_ptr->right != _ptr->right->left)
			{
				_ptr = _ptr->right;
				while (_ptr->left != _ptr->left->left)
					_ptr = _ptr->left;
			}
			else
			{
				while (_ptr == _ptr->parent->right && _ptr != _ptr->parent)
					_ptr = _ptr->parent;
				_ptr = _ptr->parent;
			}
			return (*this);
		}

		mapConstIterator& operator--()
		{
			if (_ptr == _ptr->parent) {
				while (_ptr->right != _ptr->right->left) {
					_ptr = _ptr->right;
				}
			}
			else if (_ptr->left != _ptr->left->left) {
				_ptr = _ptr->left;
				while (_ptr->right != _ptr->right->left) {
					_ptr = _ptr->right;
				}
			}
			else {
				while (_ptr == _ptr->parent->left && _ptr != _ptr->parent){
					_ptr = _ptr->parent;
				}
				_ptr = _ptr->parent;
			}
			return (*this);
		}

		mapConstIterator operator++(int)
		{
			mapConstIterator<node, Key, T> x(*this);
			this->operator++();
			return (x);
		}

		mapConstIterator operator--(int)
		{
			mapConstIterator<node, Key, T> x(*this);
			this->operator--();
			return (x);
		}

		node_type* getPtr() const { return (_ptr); }

		value_type& operator*() const { return (_ptr->data); }
		value_type* operator->() const { return (&_ptr->data); }

	private:
		node_type *_ptr;

	};
}

#endif
