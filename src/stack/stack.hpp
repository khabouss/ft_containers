#ifndef __SRC_STACK_STACK_HPP
# define __SRC_STACK_STACK_HPP

#include "../vector/vector.hpp"

namespace ft
{

template< class T, class Container = ft::vector<T> >
class stack {

public:
    typedef Container container_type;
    typedef typename Container::value_type value_type;
    typedef typename Container::size_type size_type;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;

protected:
    container_type c;

public:
    explicit stack( const Container& cont = Container() ) : c(cont) {};
    ~stack() {};
    stack& operator=( const stack& other ) { c = other.c; return *this; };
    reference top() { return this->c.back(); };
    const_reference top() const { return this->c.back(); };
    bool empty() const { return this->c.empty(); };
    size_type size() const{ return this->c.size(); };
    void push( const value_type& value ) { this->c.push_back(value); };
    void pop(){ this->c.pop_back(); };

    template< class Tf, class Containerf >
    friend bool operator==( const ft::stack<Tf,Containerf>& lhs, const ft::stack<Tf,Containerf>& rhs );

    template< class Tf, class Containerf >
    friend bool operator!=( const ft::stack<Tf,Containerf>& lhs, const ft::stack<Tf,Containerf>& rhs );

    template< class Tf, class Containerf >
    friend bool operator<( const ft::stack<Tf,Containerf>& lhs, const ft::stack<Tf,Containerf>& rhs );

    template< class Tf, class Containerf >
    friend bool operator<=( const ft::stack<Tf,Containerf>& lhs, const ft::stack<Tf,Containerf>& rhs );

    template< class Tf, class Containerf >
    friend bool operator>( const ft::stack<Tf,Containerf>& lhs, const ft::stack<Tf,Containerf>& rhs );

    template< class Tf, class Containerf >
    friend bool operator>=( const ft::stack<Tf,Containerf>& lhs, const ft::stack<Tf,Containerf>& rhs );

};

template< class T, class Container >
bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){ return lhs.c == rhs.c; };

template< class T, class Container >
bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){ return lhs.c != rhs.c; };

template< class T, class Container >
bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){ return lhs.c < rhs.c; };

template< class T, class Container >
bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){ return lhs.c <= rhs.c; };

template< class T, class Container >
bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){ return lhs.c > rhs.c; };

template< class T, class Container >
bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){ return lhs.c >= rhs.c; };

} // namespace ft

#endif // __SRC_STACK_STACK_HPP