#if !defined(_SRC_MAP_MAP_HPP__)
#define _SRC_MAP_MAP_HPP__

#include <iostream>
#include "includes/containers.hpp"
#include "../iterator/mapIterator.hpp"
#include "redBlack.hpp"

namespace ft
{

    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map
    {

    public:
        typedef struct s_node
        {
            ft::pair<const Key, T> data;
            bool color;
            struct s_node *left;
            struct s_node *right;
            struct s_node *parent;

            s_node(ft::pair<const Key, T> data) : data(data) {}

            const Key &key(void) { return (data.first); }
            
            T &val(void) { return (data.second); }
        } node;

        class ValueCompare;

        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef ValueCompare value_compare;
        typedef typename Alloc::template rebind<node>::other allocator_type;
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

        ft::redBlack<node> tree;

        class ValueCompare
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
            ValueCompare(Compare c) : comp(c) {}
            Compare comp;
        };

        explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
        {
            _alloc = alloc;
            _comp = comp;
            this->_new_nil_node();
        }

        template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
            typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type * = 0)
        {
            _alloc = alloc;
            _comp = comp;
            this->_new_nil_node();

            while (first != last)
                this->insert(*first++);
        }

        map(const map &x)
        {
            this->_new_nil_node();
            *this = x;
        }

        ~map(void)
        {
            this->clear();
            _alloc.destroy(_nil);
            _alloc.deallocate(_nil, 1);
        }

        map &operator=(const map &x)
        {
            if (this == &x)
                return (*this);

            this->clear();
            _alloc = x._alloc;
            _comp = x._comp;

            for (const_iterator it = x.begin(); it != x.end(); it++)
                this->insert(*it);
            return (*this);
        }

        iterator begin(void)
        {
            return (iterator(this->_leftmost(_nil->right)));
        }

        const_iterator begin(void) const
        {
            return (const_iterator(this->_leftmost(_nil->right)));
        }

        iterator end(void)
        {
            return (iterator(_nil));
        }

        const_iterator end(void) const
        {
            return (const_iterator(_nil));
        }

        reverse_iterator rbegin(void)
        {
            return (reverse_iterator(_nil));
        }

        const_reverse_iterator rbegin(void) const
        {
            return (const_reverse_iterator(_nil));
        }

        reverse_iterator rend(void)
        {
            return (reverse_iterator(this->_leftmost(_nil->right)));
        }

        const_reverse_iterator rend(void) const
        {
            return (const_reverse_iterator(this->_leftmost(_nil->right)));
        }

        bool empty(void) const
        {
            return (_nil == _nil->right);
        }

        size_type size(void) const
        {
            size_type n = 0;
            for (const_iterator it = this->begin(); it != this->end(); it++)
                n++;
            return (n);
        }

        size_type max_size(void) const
        {
            return (_alloc.max_size());
        }

        mapped_type &operator[](const key_type &k)
        {
            this->insert(ft::make_pair(k, mapped_type()));
            return (this->find(k)->second);
        }

        ft::pair<iterator, bool> insert(const value_type &val)
        {
            iterator it;
            if (this->count(val.first))
            {
                it = this->find(val.first);
                return (ft::make_pair(it, false));
            }
            else
            {
                it = iterator(this->_new_node(val));
                return (ft::make_pair(it, true));
            }
        }

        iterator insert(iterator position, const value_type &val)
        {
            (void)position;
            return (this->insert(val).first);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_same<InputIterator, int>::value>::type * = 0)
        {
            while (first != last)
                this->insert(*first++);
        }

        void erase(iterator position)
        {
            node *ptr = position.getPtr();

            if (ptr->left != _nil && ptr->right != _nil)
            {
                position--;
                this->_swap_nodes(ptr, position.getPtr());
                this->erase(ptr);
            }
            else
            {
                node *child = (ptr->left != _nil) ? ptr->left : ptr->right;

                if (child != _nil)
                    child->parent = ptr->parent;
                if (ptr->parent->left == ptr)
                    ptr->parent->left = child;
                else
                    ptr->parent->right = child;

                this->_removeNode(ptr, child);
            }
        }

        size_type erase(const key_type &k)
        {
            if (this->count(k))
            {
                this->erase(this->find(k));
                return (1);
            }
            return (0);
        }

        void erase(iterator first, iterator last)
        {
            for (iterator it = first++; it != last; it = first++)
                this->erase(it);
        }

        void swap(map &x)
        {
            ft::swap(_alloc, x._alloc);
            ft::swap(_comp, x._comp);
            ft::swap(_nil, x._nil);
        }

        void clear(void)
        {
            iterator first = this->begin();
            for (iterator it = first++; it != this->end(); it = first++)
                this->erase(it);
        }

        key_compare key_comp(void) const
        {
            return (key_compare());
        }

        value_compare value_comp(void) const
        {
            return (value_compare(_comp));
        }

        iterator find(const key_type &k)
        {
            if (this->count(k))
                return (iterator(this->_find_node(_nil->right, k)));
            else
                return (this->end());
        }

        const_iterator find(const key_type &k) const
        {
            if (this->count(k))
                return (const_iterator(this->_find_node(_nil->right, k)));
            else
                return (this->end());
        }

        size_type count(const key_type &k) const
        {
            size_type n = 0;
            for (const_iterator it = this->begin(); it != this->end(); it++)
            {
                if (this->_equal(k, it->first))
                    n++;
            }
            return (n);
        }

        iterator lower_bound(const key_type &k)
        {
            iterator it = this->begin();

            while (it != this->end())
            {
                if (_comp((*it).first, k) == false)
                    break;
                it++;
            }
            return (it);
        }

        const_iterator lower_bound(const key_type &key) const
        {
            const_iterator it = this->begin();

            while (it != this->end())
            {
                if (_comp((*it).first, key) == false)
                    break;
                it++;
            }
            return (it);
        }

        iterator upper_bound(const key_type &k)
        {
            iterator it = this->begin();

            while (it != this->end())
            {
                if (_comp(k, (*it).first))
                    break;
                it++;
            }
            return (it);
        }

        const_iterator upper_bound(const key_type &key) const
        {
            const_iterator it = this->begin();

            while (it != this->end())
            {
                if (_comp(key, (*it).first))
                    break;
                it++;
            }
            return (it);
        }

        ft::pair<iterator, iterator> equal_range(const key_type &k)
        {
            return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
        }

        ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
        }

        allocator_type get_allocator(void) const
        {
            return (allocator_type());
        }

        void _new_nil_node(void)
        {
            _nil = _alloc.allocate(1);
            this->_construct(_nil);
            _nil->color = BLACK_;
        }

        node *_new_node(const value_type &val = value_type())
        {
            node *new_node = _alloc.allocate(1);
            this->_construct(new_node, val);

            node *parent = this->_find_parent(_nil->right, val.first);
            if (parent == _nil || !this->_comp(val.first, parent->key()))
                parent->right = new_node;
            else
                parent->left = new_node;
            new_node->parent = parent;

            this->tree._insertRB(new_node, _nil);

            return (new_node);
        }

        void _construct(node *ptr, const value_type &val = value_type())
        {
            node tmp = node(val);
            tmp.left = _nil;
            tmp.right = _nil;
            tmp.parent = _nil;
            tmp.color = RED_;
            _alloc.construct(ptr, tmp);
        }

        void _swap_nodes(node *a, node *b)
        {
            if (a->left != b && a->left != _nil)
                a->left->parent = b;
            if (a->right != b && a->right != _nil)
                a->right->parent = b;
            if (a->parent != b && a->parent != _nil)
            {
                if (a->parent->left == a)
                    a->parent->left = b;
                else
                    a->parent->right = b;
            }

            if (b->left != a && b->left != _nil)
                b->left->parent = a;
            if (b->right != a && b->right != _nil)
                b->right->parent = a;
            if (b->parent != a && b->parent != _nil)
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

            if (_nil->right == a)
                _nil->right = b;
            else if (_nil->right == b)
                _nil->right = a;
        }

        void _removeNode(node *ptr, node *child)
        {
            this->tree._deleteRB(ptr, child, _nil);

            _alloc.destroy(ptr);
            _alloc.deallocate(ptr, 1);
        }

        node *_find_node(node *current, const key_type &k) const
        {
            if (current == _nil || this->_equal(current->key(), k))
                return (current);
            else if (this->_comp(k, current->key()))
                return (this->_find_node(current->left, k));
            else
                return (this->_find_node(current->right, k));
        }

        node *_find_parent(node *current, const key_type &k) const
        {
            if (!this->_comp(k, current->key()))
            {
                if (current->right == _nil)
                    return (current);
                else
                    return (this->_find_parent(current->right, k));
            }
            else
            {
                if (current->left == _nil)
                    return (current);
                else
                    return (this->_find_parent(current->left, k));
            }
        }

        node *_leftmost(node *root) const
        {
            while (root->left != root->left->left)
                root = root->left;
            return (root);
        }

        bool _equal(const key_type &lhs, const key_type &rhs) const
        {
            return (this->_comp(lhs, rhs) == false && this->_comp(rhs, lhs) == false);
        }

    private:
        allocator_type _alloc;
        key_compare _comp;
        node *_nil;
    };

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
