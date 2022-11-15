#include "src/map/map.hpp"       // your map path.
#include "src/vector/vector.hpp" // your Vector path.
#include "src/utils/pair.hpp"  // path to ft::pair.
// #include "map-test-helper.hpp"
#include <map>

#include <vector>
#include <iostream>
#include <iterator>
#include <utility>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <random>

template <typename Iter1, typename Iter2>
bool compareMaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        if (first1->first != first2->first || first1->second != first2->second)
            return false;
    return true;
}

int main() {
    // bool cond;
    std::map<int, char> first;
    ft::map<int, char> m_first;

    for (size_t i = 97; i < 110; i++)
    {
        first[i - 97] = i;
        m_first[i - 97] = i;
    }

    m_first.printHelper(m_first.getRoot(), "", true);

    std::map<int, char> copy(first);
    ft::map<int, char> m_copy(m_first);

    m_copy.printHelper(m_copy.getRoot(), "", true);
    // bool cond = compareMaps(first.begin(), first.end(), m_first.begin(), m_first.end());
    // std::cout << std::endl << "cond: " << cond << std::endl;

    // std::map<char, int> second(first.begin(), first.end());
    // ft::map<char, int> m_second(m_first.begin(), m_first.end());

    // cond = cond && second.size() == m_second.size() && comparemaps(second.begin(), second.end(), m_second.begin(), m_second.end());
    // std::map<char, int> third(second);
    // ft::map<char, int> m_third(m_second);

    // cond = cond && third.size() == m_third.size() && comparemaps(third.begin(), third.end(), m_third.begin(), m_third.end());

    // std::map<char, int, classcomp> fourth;  // class as Compare
    // ft::map<char, int, classcomp> m_fourth; // class as Compare

    // cond = fourth.size() == m_fourth.size() && cond && comparemaps(fourth.begin(), fourth.end(), m_fourth.begin(), m_fourth.end());

    // bool (*fn_pt)(char, char) = fncomp;
    // std::map<char, int, bool (*)(char, char)> fifth(fn_pt);  // function pointer as Compare
    // ft::map<char, int, bool (*)(char, char)> m_fifth(fn_pt); // function pointer as Compare

    // cond = fifth.size() == m_fifth.size() && cond && comparemaps(fifth.begin(), fifth.end(), m_fifth.begin(), m_fifth.end());

    // first = std::map<char, int>();
    // m_first = ft::map<char, int>();

    // cond = copy.size() == m_copy.size() && cond && comparemaps(copy.begin(), copy.end(), m_copy.begin(), m_copy.end());
    // return cond;
    // std::cout << cond << std::endl;
}