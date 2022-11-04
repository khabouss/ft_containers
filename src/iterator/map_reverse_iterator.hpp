#if !defined(MAP_REV_ITERATOR)
#define MAP_REV_ITERATOR

#include <iostream>
#include "iterator.hpp"
#include "../map/avl_tree.hpp"
#define _REV_ITERATOR ft::iterator<std::bidirectional_iterator_tag, T> // <--

namespace ft
{

    template <class T, class pair>
    class TreeReverseIterator : ft::iterator<std::bidirectional_iterator_tag, T>
    {

    private:
        T *_ptr;

    public:
        typedef typename _REV_ITERATOR::difference_type difference_type;
        typedef typename _REV_ITERATOR::value_type value_type;
        typedef typename _REV_ITERATOR::iterator_category iterator_category;
        typedef T *pointer;
        typedef T &reference;
        typedef pair *pair_type_pointer;
        typedef pair &pair_type_refrence;

        TreeReverseIterator(void) { _ptr = NULL; };
        TreeReverseIterator(T *node) : _ptr(node) {};
        TreeReverseIterator(const TreeReverseIterator<T, pair> & it) {
            this->_ptr = it._ptr;
        }
        TreeReverseIterator(const TreeConstReverseIterator<T, pair> & it) {
            this->_ptr = it._ptr;
        }
        ~TreeReverseIterator() {};

        T getNode() {
            return *_ptr;
        }

        T* getNodePtr() {
            return _ptr;
        }

        TreeReverseIterator &operator=(const TreeReverseIterator &bst_it)
        {
            if (*this == bst_it)
                return (*this);
            this->_ptr = bst_it._ptr;
            return (*this);
        }

        bool operator==(const TreeReverseIterator& bst_it){ return (this->_ptr == bst_it._ptr); }

        bool operator!=(const TreeReverseIterator& bst_it){ return (this->_ptr != bst_it._ptr); }      

        pair_type_refrence operator*() const { return (this->_ptr->key); }        

        pair_type_pointer operator->() const { return (&this->_ptr->key); }

        TreeReverseIterator& operator++(void) {
            previousNode();
            return *this;
        }

        TreeReverseIterator operator++(int) {
            TreeReverseIterator<T, pair> tmp(*this);
            this->previousNode();
            return tmp;
        }

        TreeReverseIterator& operator--(void) {
            nextNode();
            return *this;
        }

        TreeReverseIterator operator--(int) {
            TreeReverseIterator<T, pair> tmp(*this);
            this->nextNode();
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
    class TreeConstReverseIterator : ft::iterator<std::bidirectional_iterator_tag, T>
    {

    private:
        T *_ptr;

    public:
        typedef typename _REV_ITERATOR::difference_type difference_type;
        typedef typename _REV_ITERATOR::value_type value_type;
        typedef typename _REV_ITERATOR::iterator_category iterator_category;
        typedef T *pointer;
        typedef T &reference;
        typedef pair *pair_type_pointer;
        typedef pair &pair_type_refrence;

        TreeConstReverseIterator(void) { _ptr = NULL; };
        TreeConstReverseIterator(T *node) : _ptr(node) {};
        TreeConstReverseIterator(const TreeConstReverseIterator<T, pair> & it) {
            this->_ptr = it._ptr;
        }
        TreeConstReverseIterator(const TreeReverseIterator<T, pair> & it) {
            this->_ptr = it._ptr;
        }
        ~TreeConstReverseIterator() {};

        T getNode() {
            return *_ptr;
        }

        T* getNodePtr() {
            return _ptr;
        }

        TreeConstReverseIterator &operator=(const TreeConstReverseIterator &bst_it)
        {
            if (*this == bst_it)
                return (*this);
            this->_ptr = bst_it._ptr;
            return (*this);
        }

        bool operator==(const TreeConstReverseIterator& bst_it){ return (this->_ptr == bst_it._ptr); }

        bool operator!=(const TreeConstReverseIterator& bst_it){ return (this->_ptr != bst_it._ptr); }      

        pair_type_refrence operator*() const { return (this->_ptr->key); }        

        pair_type_pointer operator->() const { return (&this->_ptr->key); }

        TreeConstReverseIterator& operator++(void) {
            previousNode();
            return *this;
        }

        TreeConstReverseIterator operator++(int) {
            TreeConstReverseIterator<T, pair> tmp(*this);
            this->previousNode();
            return tmp;
        }

        TreeConstReverseIterator& operator--(void) {
            nextNode();
            return *this;
        }

        TreeConstReverseIterator operator--(int) {
            TreeConstReverseIterator<T, pair> tmp(*this);
            this->nextNode();
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
