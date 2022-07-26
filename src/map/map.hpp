#if !defined(_SRC_MAP_MAP_HPP__)
#define _SRC_MAP_MAP_HPP__

#include <iostream>
#include "../utils/headers.hpp"
#include "../iterator/mapIterator.hpp"
#include "redBlack.hpp"

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map
    {

    public:

        class value_compare;
        class node;

        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef value_compare value_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef ft::mapIterator<node, Key, T> iterator;
        typedef ft::mapConstIterator<node, Key, T> const_iterator;
        typedef ft::map_reverse_iterator<iterator> reverse_iterator;
        typedef ft::map_reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename mapIterator<node, Key, T>::difference_type difference_type;
        typedef typename mapIterator<node, Key, T>::size_type size_type;

        class node
        {

        public:
            class node *parent;
            class node *left;
            class node *right;
            value_type data;
            bool color;

            node(value_type data) : data(data) {}

            key_type const &getKey() { return (data.first); }
            mapped_type &getValue() { return (data.second); }
        };

        typedef typename std::allocator<node > node_allocator;

        ft::redBlack<node, Compare> tree;

        class value_compare
        {
        public:
            friend class map;
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator()(const value_type &x, const value_type &y) const
            {
                return (comp(x.first, y.first));
            }

        protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {}
        };

        explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
            : tree(), _alloc(alloc), _comp(comp) { initNilNode(); }

        template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
            typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type * = 0)
            : tree(), _alloc(alloc), _comp(comp)
        {
            initNilNode();
            while (first != last)
            {
                insert(*first++);
            }
        }

        map(const map &x)
        {
            initNilNode();
            *this = x;
        }

        ~map()
        {
            clear();
            _alloc.destroy(nil);
            _alloc.deallocate(nil, 1);
        }

        map &operator=(const map &other)
        {
            if (this == &other)
                return (*this);
            clear();
            _alloc = other._alloc;
            _comp = other._comp;
            insert(other.begin(), other.end());
            return (*this);
        }

        iterator begin()
        {
            return (iterator(leftMostNode(nil->right)));
        }

        const_iterator begin() const
        {
            return (const_iterator(leftMostNode(nil->right)));
        }

        iterator end()
        {
            return (iterator(nil));
        }

        const_iterator end() const
        {
            return (const_iterator(nil));
        }

        reverse_iterator rbegin()
        {
            return (reverse_iterator(nil));
        }

        const_reverse_iterator rbegin() const
        {
            return (const_reverse_iterator(nil));
        }

        reverse_iterator rend()
        {
            return (reverse_iterator(leftMostNode(nil->right)));
        }

        const_reverse_iterator rend() const
        {
            return (const_reverse_iterator(leftMostNode(nil->right)));
        }

        bool empty() const
        {
            return (begin() == end());
        }

        size_type size() const
        {
            return (tree.size());
        }

        size_type max_size() const
        {
            return (_alloc.max_size());
        }

        mapped_type &operator[](const key_type &k)
        {
            insert(ft::make_pair(k, mapped_type()));
            return (find(k)->second);
        }


        ft::pair<iterator, bool> insert(const value_type &val)
        {
            iterator it = findNodeByValue(nil->right, val);
            if (it != nil)
            {
                return (ft::make_pair(it, false));
            }
            else
            {
                it = iterator(makeNode(val));
                return (ft::make_pair(it, true));
            }
        }

        iterator insert(iterator position, const value_type &val)
        {
            (void)position;
            return (insert(val).first);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type * = 0)
        {
            while (first != last)
                insert(*first++);
        }

        void erase(iterator position)
        {
            node *ptr = position.getPtr();

            if (ptr->left != nil && ptr->right != nil)
            {
                position--;
                swapNode(ptr, position.getPtr());
                erase(iterator(ptr));
            }
            else
            {
                node *child = (ptr->left != nil) ? ptr->left : ptr->right;

                if (child != nil)
                    child->parent = ptr->parent;
                if (ptr->parent->left == ptr)
                    ptr->parent->left = child;
                else
                    ptr->parent->right = child;

                removeNode(ptr);
            }
        }

        size_type erase(const key_type &k)
        {
            iterator it = findNode(nil->right, k);
            if (it != nil)
            {
                erase(it);
                return (1);
            }
            return (0);
        }

        void erase(iterator first, iterator last)
        {
            iterator it = first++;

            while (it != last)
            {
                erase(it);
                it = first++;
            }
        }

        void swap(map &x)
        {
            ft::swap(_alloc, x._alloc);
            ft::swap(_comp, x._comp);
            ft::swap(nil, x.nil);
            size_t oldsize = x.tree.size();
            x.tree.setSize(this->tree.size());
            this->tree.setSize(oldsize);
        }

        void clear()
        {
            erase(begin(), end());
        }

        key_compare key_comp() const
        {
            return (key_compare());
        }

        value_compare value_comp() const
        {
            return (value_compare(_comp));
        }

        iterator find(const key_type &k)
        {
            return (iterator(findNode(nil->right, k)));
        }

        const_iterator find(const key_type &k) const
        {
            return (const_iterator(findNode(nil->right, k)));
        }

        size_type count(const key_type &k) const
        {
            node* s = findNode(nil->right, k);
            return (s != nil);
        }

        iterator lower_bound(const key_type &k)
        {
            node*	x = nil->right;
            node*	lower = nil;
        
            while (x != nil)
            {
                if (!_comp(x->data.first, k))
                    {       lower = x; x = x->left;        }
                else         x = x->right;
            }
            return iterator(lower);
        }

        const_iterator lower_bound(const key_type &k) const
        {
            node*	x = nil->right;
            node*	lower = nil;
        
            while (x != nil)
            {
                if (!_comp(x->data.first, k))
                    {       lower = x; x = x->left;        }
                else         x = x->right;
            }
            return const_iterator(lower);
        }

        iterator upper_bound(const key_type &k)
        {
            node*	x = nil->right;
            node*	upper = nil;
        
            while (x != nil)
            {
                if (_comp(k, x->data.first))
                    {       upper = x; x = x->left;        }
                else         x = x->right;
            }
            return iterator(upper);
        }

        const_iterator upper_bound(const key_type &k) const
        {
            node*	x = nil->right;
            node*	upper = nil;
        
            while (x != nil)
            {
                if (_comp(k, x->data.first))
                    {       upper = x; x = x->left;        }
                else         x = x->right;
            }
            return const_iterator(upper);
        }

        ft::pair<iterator, iterator> equal_range(const key_type &k)
        {
            return (ft::make_pair(lower_bound(k), upper_bound(k)));
        }

        ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            return (ft::make_pair(lower_bound(k), upper_bound(k)));
        }

        allocator_type get_allocator() const
        {
            return (allocator_type());
        }

    private:

        void initNilNode()
        {
            nil = _alloc.allocate(1);
            constructNode(nil);
            nil->color = BLACK;
        }

        node *findNodeByValue(node *current, const value_type &k) const
        {
            if (current == nil || equal2(current->data, k))
                return (current);
            else if (_comp(k.first, current->data.first))
                return (findNodeByValue(current->left, k));
            else
                return (findNodeByValue(current->right, k));
        }

        node *makeNode(const value_type &val = value_type())
        {
            node *new_node = _alloc.allocate(1);
            constructNode(new_node, val);

            node *parent = findParent(nil->right, val.first);
            if (parent == nil || !_comp(val.first, parent->getKey()))
                parent->right = new_node;
            else
                parent->left = new_node;
            new_node->parent = parent;

            tree.insertNode(new_node, nil);
            tree.incSize();

            return (new_node);
        }

        node * getRoot() {
            return nil->right;
        }

        void constructNode(node *ptr, const value_type &val = value_type())
        {
            node tmp = node(val);
            tmp.left = nil;
            tmp.right = nil;
            tmp.parent = nil;
            tmp.color = RED;
            _alloc.construct(ptr, tmp);
        }

        void swapNode(node *a, node *b)
        {
            if (a->left != b && a->left != nil)
                a->left->parent = b;
            if (a->right != b && a->right != nil)
                a->right->parent = b;
            if (a->parent != b && a->parent != nil)
            {
                if (a->parent->left == a)
                    a->parent->left = b;
                else
                    a->parent->right = b;
            }

            if (b->left != a && b->left != nil)
                b->left->parent = a;
            if (b->right != a && b->right != nil)
                b->right->parent = a;
            if (b->parent != a && b->parent != nil)
            {
                if (b->parent->left == b)
                    b->parent->left = a;
                else
                    b->parent->right = a;
            }

            if (a->parent == b)
                a->parent = a;
            if (a->left == b)
                a->left = a;
            if (a->right == b)
                a->right = a;
            if (b->parent == a)
                b->parent = b;
            if (b->left == a)
                b->left = b;
            if (b->right == a)
                b->right = b;

            ft::swap(a->parent, b->parent);
            ft::swap(a->left, b->left);
            ft::swap(a->right, b->right);
            ft::swap(a->color, b->color);

            if (nil->right == a)
                nil->right = b;
            else if (nil->right == b)
                nil->right = a;
        }

        void removeNode(node *ptr)
        {
            tree.deleteNode2(ptr, nil, _comp);
            tree.decSize();
            _alloc.destroy(ptr);
            _alloc.deallocate(ptr, 1);
        }

        node *findNode(node *current, const key_type &k) const
        {
            if (current == nil || equal(current->getKey(), k))
                return (current);
            else if (_comp(k, current->getKey()))
                return (findNode(current->left, k));
            else
                return (findNode(current->right, k));
        }

        node *findParent(node *current, const key_type &k) const
        {
            if (!_comp(k, current->getKey()))
            {
                if (current->right == nil)
                    return (current);
                else
                    return (findParent(current->right, k));
            }
            else
            {
                if (current->left == nil)
                    return (current);
                else
                    return (findParent(current->left, k));
            }
        }

        node *leftMostNode(node *root) const
        {
            while (root->left && root->left != root->left->left)
                root = root->left;
            return (root);
        }

        bool equal(const key_type &lhs, const key_type &rhs) const
        {
            return (_comp(lhs, rhs) == false && _comp(rhs, lhs) == false);
        }

        bool equal2(const value_type &lhs, const value_type &rhs) const
        {
            return (_comp(lhs.first, rhs.first) == false && _comp(rhs.first, lhs.first) == false);
        }

        node_allocator _alloc;
        key_compare _comp;
        node *nil;
    
    
    }; // map



    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return (!(lhs == rhs));
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return (!(rhs < lhs));
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return (rhs < lhs);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return (!(lhs < rhs));
    }
    template <class Key, class T, class Compare, class Alloc>
    void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
    {
        x.swap(y);
    }

} // namespace ft

#endif // _SRC_MAP_MAP_HPP__
