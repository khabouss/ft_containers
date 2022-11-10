#if !defined(_SRC_MAP_MAP_HPP__)
#define _SRC_MAP_MAP_HPP__

#include "../pair/pair.hpp"
#include <functional>
#include <memory>
#include <iostream>
#include "avl_tree.hpp"
#include "../pair/pair.hpp"
#include "../utils/utils.hpp"
#include "../iterator/map_reverse_iterator.hpp"
#include "../iterator/map_iterator.hpp"

namespace ft
{

    template <class Arg1, class Arg2, class Result>
    struct binary_function
    {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    };

    template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {

    private:
        Allocator _alloc;

    protected:
        Compare _comp;

    public:
        avl_tree<ft::pair<Key, T> > tree;
        typedef Key key_type;
        typedef T mapped_type;
        typedef typename ft::pair<Key, T> value_type;
        typedef typename std::size_t size_type;
        typedef typename std::ptrdiff_t difference_type;
        typedef Compare key_compare;
        
        

        class value_compare : ft::binary_function<value_type, value_type, bool>
        {
            friend class map<key_type, mapped_type, key_compare, Allocator>;

        protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {}

        public:
            bool operator()(const value_type &x, const value_type &y) const
            {
                return (comp(x.first, y.first));
            }
        };

        typedef Allocator allocator_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef typename ft::avl_tree<ft::pair<Key, T> > tree_type;
        typedef typename tree_type::Node node_type;
        typedef typename ft::TreeIterator<node_type, value_type> iterator;             // <--
        typedef typename ft::TreeConstIterator<node_type, value_type> const_iterator;             // <--
        typedef typename ft::TreeReverseIterator<node_type, value_type> reverse_iterator;             // <--
        typedef typename ft::TreeReverseIterator<node_type, value_type> const_reverse_iterator;             // <--

        node_type* _null;

        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type())
            : _alloc(alloc), _comp(comp) { };

        template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr) 
        : _alloc(alloc), _comp(comp)
        {
            this->insert(first, last);
        }

        map(const map &x) : _alloc(x._alloc), _comp(x._comp) {
            this->insert(x.begin(), x.end());
        }

        ~map() {  }

        map &operator=(const map &other)
        {
            if (&other == this)
                return (*this);
            // this->clear();
            this->insert(other.begin(), other.end());
            return (*this);
        }

        allocator_type get_allocator() const {
            return this->_alloc;
        }

        T &at(const Key &key) {
            node_type *node = find(key).getNodePtr();
            if (node == NULL)
                return (NULL);
            return node->key.second;
        }

        const T &at(const Key &key) const {
            const T r = this->at(key);
            return r;
        }

        mapped_type &operator[](const key_type &key) {
            node_type *node = find(key).getNodePtr();
            if (node == NULL)
                this->insert(ft::make_pair(key, mapped_type()));
            return find(key).getNodePtr()->key.second;
        }

        iterator begin() { 
            iterator it = iterator(tree.leftMostNode(tree.root));
            it.setNull(_null);
            return it;
        }

        const_iterator begin() const { 
            const_iterator it = const_iterator(tree.leftMostNode(tree.root));
            it.setNull(_null);
            return it;
        }
        iterator end() {
            iterator it = iterator(_null);
            it.setNull(_null);
            it.setLastNode(tree.rightMostNode(tree.root));
            return it;
        }
        const_iterator end() const { 
            const_iterator it = const_iterator(_null);
            it.setNull(_null);
            it.setLastNode(tree.rightMostNode(tree.root));
            return it;
        }

        reverse_iterator rbegin() { return (reverse_iterator(this->end())); }
        const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->end())); }

        reverse_iterator rend() { return (reverse_iterator(this->begin())); }
        const_reverse_iterator rend() const { return (const_reverse_iterator(this->begin())); }

        bool empty() const {
            return this->size() == 0;
        }

        size_type size() const {
            iterator it = this->begin();
            int size = 0;
            while (it != this->end())
            {
                it++;
                size++;
            }
            return size;
        }

        size_type max_size() const {
            return _alloc.max_size();
        }

        void clear() { this->erase(this->begin(), this->end()); }

        ft::pair<iterator, bool> insert(const value_type &value)
        {
            return tree.insertNode(value);
        }

        iterator insert(iterator pos, const value_type &value) {
            (void)pos;
			return (tree.insertNode(value).first);
        }

        template <class InputIterator>
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
        insert(InputIterator first, InputIterator last) {
            difference_type n = ft::distance(first, last);
			while (n--)
				this->insert(*(first++));
        }

        void erase(iterator pos) {
            tree.root = tree.deleteNode(tree.root, pos.getNode().key);
        }

        void erase (iterator first, iterator last)
		{
			while (first != last){
                this->erase((*(first)).first); // <--- inf loop
                first = iterator(tree.leftMostNode(tree.root));
            }
		}

        size_type erase(const Key &key) {
            node_type *tobeDeleted = find(key).getNodePtr();
            if (tobeDeleted == NULL)
                return (0);
            tree.root = tree.deleteNode(tree.root, tobeDeleted->key);
            return (1);
        }

        void swap(map &other) {
            if (other == *this)
                return;
            tree.swap(other.tree);
        }

        size_type count(const key_type &k)
        {
            iterator it = this->begin();
            while (it != this->end())
                if ((*(it++)).first == k)
                    return (1);
            return (0);
        }

        iterator find(const Key &key) {
            node_type * n = tree.find(key);
            iterator it = iterator(n); // should set null in it
            it.setNull(_null);
            return it;
        }

        const_iterator find(const Key &key) const {
            node_type * n = tree.find(key);
            const_iterator it = const_iterator(n); // should set null in it
            it.setNull(_null);
            return it;
        }

        ft::pair<iterator, iterator> equal_range(const key_type &key)
        {
            return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
        }

        std::pair<const_iterator, const_iterator> equal_range(const Key &key) const {
            return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
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

        const_iterator lower_bound(const Key &key) const {
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

        const_iterator upper_bound(const Key &key) const {
            const_iterator it = this->begin();

            while (it != this->end())
            {
                if (_comp(key, (*it).first))
                    break;
                it++;
            }
            return (it);
        }

        key_compare key_comp() const { return key_compare(); }

        value_compare value_comp() const { return (value_compare(key_compare())); }
    };

    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        typename ft::map<Key, T, Compare, Alloc>::iterator lhs_it = lhs.begin();
        typename ft::map<Key, T, Compare, Alloc>::iterator lhs_end = lhs.end();
        typename ft::map<Key, T, Compare, Alloc>::iterator rhs_it = rhs.begin();
        typename ft::map<Key, T, Compare, Alloc>::iterator rhs_end = rhs.end();

        while (lhs_it != lhs_end)
		{
			if (rhs_it == rhs_end || *rhs_it != *lhs_it)
				return (false);
			++lhs_it, ++rhs_it;
		}

		return (rhs_it == rhs_end);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs) { return !(lhs == rhs); }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs,
                   const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs) { return (lhs < rhs) || lhs == rhs; }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs,
                   const ft::map<Key, T, Compare, Alloc> &rhs) { return !(lhs < rhs) && !(lhs == rhs); }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)  { return (lhs > rhs) || lhs == rhs; }

    template <class Key, class T, class Compare, class Alloc>
    void swap(ft::map<Key, T, Compare, Alloc> &lhs,
              ft::map<Key, T, Compare, Alloc> &rhs) { lhs.swap(rhs); }

} // namespace ft

#endif // _SRC_MAP_MAP_HPP__
