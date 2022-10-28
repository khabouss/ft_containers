#if !defined(_SRC_MAP_MAP_HPP__)
#define _SRC_MAP_MAP_HPP__

#include "../pair/pair.hpp"
#include <functional>
#include <memory>
#include <iostream>

/* WORKFLOW

what is less ? check

what is binary_function ?
what is value_compare ?
last - remove std versions

*/


namespace ft
{

template <class Arg1, class Arg2, class Result>
struct binary_function
{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

template<class Key, class T, class Compare = std::less<Key>
, class Allocator = std::allocator<ft::pair<const Key, T> > > 
class map {

private:
    Allocator _alloc;

public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef typename ft::pair<const Key, T> value_type;
    typedef typename std::size_t size_type;
    typedef typename std::ptrdiff_t difference_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef typename std::iterator<std::bidirectional_iterator_tag, value_type> iterator; // <--
    typedef typename std::iterator<std::bidirectional_iterator_tag, const value_type> const_iterator; // <--
    typedef typename std::reverse_iterator<iterator> reverse_iterator;
    typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator;

    class value_compare : public ft::binary_function<value_type, value_type, bool> {
    protected:
        Compare comp;
    public:
        value_compare( Compare c ) : comp(c) {}
        bool operator()( const value_type& lhs, const value_type& rhs ) const {
            return comp(lhs, rhs);
        }
    };

    explicit map(const key_compare &comp = key_compare(),
                 const allocator_type &alloc = allocator_type());

    template <class InputIterator>
    map(InputIterator first, InputIterator last,
        const key_compare &comp = key_compare(),
        const allocator_type &alloc = allocator_type());

    map(const map &x);

    ~map() {}

    map& operator=( const map& other );

    allocator_type get_allocator() const;

    T& at( const Key& key );
    const T& at( const Key& key ) const;

    T& operator[]( const Key& key );

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;

    reverse_iterator rend();
    const_reverse_iterator rend() const;

    bool empty() const;

    size_type size() const;

    size_type max_size() const;

    void clear();

    std::pair<iterator, bool> insert( const value_type& value );

    iterator insert( iterator pos, const value_type& value );

    template< class InputIt >
    void insert( InputIt first, InputIt last );

    iterator erase( iterator pos );

    iterator erase( iterator first, iterator last );

    size_type erase( const Key& key );

    void swap( map& other );

    size_type count( const Key& key ) const;

    iterator find( const Key& key );

    const_iterator find( const Key& key ) const;

    std::pair<iterator,iterator> equal_range( const Key& key );

    std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;

    iterator lower_bound( const Key& key );

    const_iterator lower_bound( const Key& key ) const;

    iterator upper_bound( const Key& key );

    const_iterator upper_bound( const Key& key ) const;

    key_compare key_comp() const;

    value_compare value_comp() const;

};

template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs );

template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs );

template< class Key, class T, class Compare, class Alloc >
bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs );

template< class Key, class T, class Compare, class Alloc >
bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs );

template< class Key, class T, class Compare, class Alloc >
bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs );

template< class Key, class T, class Compare, class Alloc >
bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs );

template< class Key, class T, class Compare, class Alloc >
void swap( ft::map<Key,T,Compare,Alloc>& lhs,
           ft::map<Key,T,Compare,Alloc>& rhs );
    
} // namespace ft


#endif // _SRC_MAP_MAP_HPP__
