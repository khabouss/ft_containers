#if !defined(MAP_ITERATOR)
#define MAP_ITERATOR

#include <iostream>
#include "iterator.hpp"
#include "../map/avl_tree.hpp"
#define _ITERATOR ft::iterator<std::bidirectional_iterator_tag, T> // <--

namespace ft
{

    template <class T, class pair>
    class TreeIterator : ft::iterator<std::bidirectional_iterator_tag, T>
    {

    private:
        T *_ptr;

    public:
        typedef typename _ITERATOR::difference_type difference_type;
        typedef typename _ITERATOR::value_type value_type;
        typedef typename _ITERATOR::iterator_category iterator_category;
        typedef T *pointer;
        typedef T &reference;
        typedef pair *pair_type_pointer;
        typedef pair &pair_type_refrence;

        TreeIterator(void) { _ptr = NULL; };
        TreeIterator(T *node) : _ptr(node) {};
        TreeIterator(const TreeIterator<T, pair> & it) {
            this->_ptr = it._ptr;
        }
        TreeIterator(const TreeConstIterator<T, pair> & it) {
            this->_ptr = it._ptr;
        }
        ~TreeIterator() {};

        T getNode() {
            return *_ptr;
        }

        T* getNodePtr() {
            return _ptr;
        }

        TreeIterator &operator=(const TreeIterator &bst_it)
        {
            if (*this == bst_it)
                return (*this);
            this->_ptr = bst_it._ptr;
            return (*this);
        }
        
        TreeIterator &operator=(const TreeConstIterator &bst_it)
        {
            if (*this == bst_it)
                return (*this);
            this->_ptr = bst_it._ptr;
            return (*this);
        }

        bool operator==(const TreeIterator& bst_it){ return (this->_ptr == bst_it._ptr); }

        bool operator!=(const TreeIterator& bst_it){ return (this->_ptr != bst_it._ptr); }      

        pair_type_refrence operator*() const { return (this->_ptr->key); }        

        pair_type_pointer operator->() const { return (&this->_ptr->key); }

        TreeIterator& operator++(void) {
            nextNode();
            return *this;
        }

        TreeIterator operator++(int) {
            TreeIterator<T, pair> tmp(*this);
            this->nextNode();
            return tmp;
        }

        TreeIterator& operator--(void) {
            previousNode();
            return *this;
        }

        TreeIterator operator--(int) {
            TreeIterator<T, pair> tmp(*this);
            this->previousNode();
            return tmp;
        }


        void nextNode(void)
        {
            if (_ptr && _ptr->right && (_ptr->right != _ptr->right->left))
            {
                _ptr = _ptr->right;
                while (_ptr && _ptr->left && (_ptr->left != _ptr->left->left))
                    _ptr = _ptr->left;
            }
            else
            {
                while (_ptr && _ptr->parent && _ptr == _ptr->parent->right && _ptr != _ptr->parent)
                    _ptr = _ptr->parent;
                _ptr = _ptr->parent;
            }
        }

        void previousNode(void)
        {
            if (_ptr && _ptr->parent && _ptr == _ptr->parent)
            {
                while (_ptr && _ptr->right && _ptr->right != _ptr->right->left)
                    _ptr = _ptr->right;
            }
            else if (_ptr && _ptr->left && _ptr->left != _ptr->left->left)
            {
                _ptr = _ptr->left;
                while (_ptr && _ptr->right != _ptr->right->left)
                    _ptr = _ptr->right;
            }
            else
            {
                while (_ptr && _ptr->parent && _ptr == _ptr->parent->left && _ptr != _ptr->parent)
                    _ptr = _ptr->parent;
                _ptr = _ptr->parent;
            }
        }
    };


    template <class T, class pair>
    class TreeConstIterator : ft::iterator<std::bidirectional_iterator_tag, T>
    {

    private:
        T *_ptr;

    public:
        typedef typename _ITERATOR::difference_type difference_type;
        typedef typename _ITERATOR::value_type value_type;
        typedef typename _ITERATOR::iterator_category iterator_category;
        typedef T *pointer;
        typedef T &reference;
        typedef pair *pair_type_pointer;
        typedef pair &pair_type_refrence;

        TreeConstIterator(void) { _ptr = NULL; };
        TreeConstIterator(T *node) : _ptr(node) {};
        TreeConstIterator(const TreeConstIterator<T, pair> & it) {
            this->_ptr = it._ptr;
        }
        TreeConstIterator(const TreeIterator<T, pair> & it) {
            this->_ptr = it._ptr;
        }

        ~TreeConstIterator() {};

        T getNode() {
            return *_ptr;
        }

        T* getNodePtr() {
            return _ptr;
        }

        TreeConstIterator &operator=(const TreeConstIterator &bst_it)
        {
            if (*this == bst_it)
                return (*this);
            this->_ptr = bst_it._ptr;
            return (*this);
        }

        TreeConstIterator &operator=(const TreeIterator &bst_it)
        {
            if (*this == bst_it)
                return (*this);
            this->_ptr = bst_it._ptr;
            return (*this);
        }

        bool operator==(const TreeConstIterator& bst_it){ return (this->_ptr == bst_it._ptr); }

        bool operator!=(const TreeConstIterator& bst_it){ return (this->_ptr != bst_it._ptr); }      

        pair_type_refrence operator*() const { return (this->_ptr->key); }        

        pair_type_pointer operator->() const { return (&this->_ptr->key); }

        TreeConstIterator& operator++(void) {
            nextNode();
            return *this;
        }

        TreeConstIterator operator++(int) {
            TreeConstIterator<T, pair> tmp(*this);
            this->nextNode();
            return tmp;
        }

        TreeConstIterator& operator--(void) {
            previousNode();
            return *this;
        }

        TreeConstIterator operator--(int) {
            TreeConstIterator<T, pair> tmp(*this);
            this->previousNode();
            return tmp;
        }


        void nextNode(void)
        {
            if (_ptr && _ptr->right && (_ptr->right != _ptr->right->left))
            {
                _ptr = _ptr->right;
                while (_ptr && _ptr->left && (_ptr->left != _ptr->left->left))
                    _ptr = _ptr->left;
            }
            else
            {
                while (_ptr && _ptr->parent && _ptr == _ptr->parent->right && _ptr != _ptr->parent)
                    _ptr = _ptr->parent;
                _ptr = _ptr->parent;
            }
        }

        void previousNode(void)
        {
            if (_ptr && _ptr->parent && _ptr == _ptr->parent)
            {
                while (_ptr && _ptr->right && _ptr->right != _ptr->right->left)
                    _ptr = _ptr->right;
            }
            else if (_ptr && _ptr->left && _ptr->left != _ptr->left->left)
            {
                _ptr = _ptr->left;
                while (_ptr && _ptr->right != _ptr->right->left)
                    _ptr = _ptr->right;
            }
            else
            {
                while (_ptr && _ptr->parent && _ptr == _ptr->parent->left && _ptr != _ptr->parent)
                    _ptr = _ptr->parent;
                _ptr = _ptr->parent;
            }
        }
    };

} // namespace ft

#endif // MAP_ITERATOR
