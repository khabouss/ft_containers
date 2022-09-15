#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{

    template <class T1, class T2>
        struct pair
        {
            public :

                // Member types :

                /* The first template argument type */
                typedef T1 first_type;

                /* The second template argument type */
                typedef T2 second_type;

                // Member variables :

                /* The first value in the pair */
                first_type first;

                /* The second value in the pair */
                second_type second;

                /*
                ** @brief Default.
                ** Construct a pair object with its element
                ** value-initialized.
                */
                pair()
                :
                    first(),
                    second()
                {}

                /*
                ** @brief Copy.
                ** The pair is initialized with the content
                ** of "pr". The "pr" first is passed to this
                ** first, same for second of each.
                **
                ** @param pr the pair to copy.
                */
                template<class U, class V>
                    pair (const pair<U, V>& pr)
                    :
                        first(pr.first),
                        second(pr.second)
                    {}

                /*
                ** @brief Initialization.
                ** Member "first" is constructed with a.
                ** Member "second" is constructed with b.
                **
                ** @param a to member first.
                ** @param b to member second.
                */
                pair (const first_type& a, const second_type& b)
                :
                    first(a),
                    second(b)
                {}

                /*
                ** @brief Assigns "pr" member (first, second) to this.
                **
                ** @param pr the pair object to copy.
                */
                pair& operator= (const pair& pr)
                {
                    if (*this == pr)
                        return (*this);
                    this->first = pr.first;
                    this->second = pr.second;
                    return (*this);
                }
        };
    
    /*
    ** @brief Equal comparison between two pair object.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class T1, class T2>
        bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return (lhs.first == rhs.first && lhs.second == rhs.second);
        }

    /*
    ** @brief Difference comparison between two pair object.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class T1, class T2>
        bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return !(lhs == rhs);
        }
    
    /*
    ** @brief Inferior comparison between two pair object.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class T1, class T2>
        bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
        }

    /*
    ** @brief Inferior or equal comparison between two pair object.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class T1, class T2>
        bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return !(rhs < lhs);
        }

    /*
    ** @brief Superior comparison between two pair object.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class T1, class T2>
        bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return (rhs < lhs);
        }

    /*
    ** @brief Superior or equal comparison between two pair object.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class T1, class T2>
        bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return !(lhs < rhs);
        }
    
    /*
    ** @bref Construct a pair object with
    ** "x" and "y".
    **
    ** @param x, y elements. (can have different types).
    ** @return the pair object.
    */
    template <class T1, class T2>
        ft::pair<T1,T2> make_pair(T1 x, T2 y)
        {
            return (ft::pair<T1, T2>(x, y));
        }
    
} // namespace ft



#endif