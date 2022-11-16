#include "../src/vector/vector.hpp"
#include "../src/map/map.hpp"
#include "../src/stack/stack.hpp"
#include "../src/utils/headers.hpp"

#if 0
    # define NS ft
#else
    #include <vector>
    #include <stack>
    # define NS std
#endif


int main() {

    {
        std::cout << " _________________ Testing construct _____________________ \n" << std::endl;
        NS::vector<int> myvector(2, 200); // vector with 2 elements

        NS::stack<int, NS::vector<int> > first; // empty stack using vector
        NS::stack<int, NS::vector<int> > second(myvector);

        std::cout << "size of first: " << first.size() << '\n';
        std::cout << "size of second: " << second.size() << '\n';

        std::cout << " -------------------------- \n\n" << std::endl;
    }


    {
        std::cout << " _________________ Testing empty() _____________________ \n" << std::endl;
        NS::stack<int> mystack;
        int sum(0);

        for (int i = 1; i <= 10; i++)
            mystack.push(i);

        while (!mystack.empty())
        {
            sum += mystack.top();
            mystack.pop();
        }

        std::cout << "total: " << sum << '\n';

        std::cout << " -------------------------- \n\n" << std::endl;
    }


    {
        std::cout << " _________________ Testing size _____________________ \n" << std::endl;
        NS::stack<int> myints;
        std::cout << "0. size: " << myints.size() << '\n';

        for (int i = 0; i < 5; i++)
            myints.push(i);
        std::cout << "1. size: " << myints.size() << '\n';

        myints.pop();
        std::cout << "2. size: " << myints.size() << '\n';

        std::cout << " -------------------------- \n\n" << std::endl;
    }


    {
        std::cout << " _________________ Testing top _____________________ \n" << std::endl;
        NS::stack<int> mystack;

        mystack.push(10);
        mystack.push(20);

        mystack.top() -= 5;

        std::cout << "mystack.top() is now " << mystack.top() << '\n';

        std::cout << " -------------------------- \n\n" << std::endl;
    }


    {
        std::cout << " _________________ Testing push and pop _____________________ \n" << std::endl;

        NS::stack<int> mystack;

        for (int i = 0; i < 5; ++i)
            mystack.push(i);

        std::cout << "Popping out elements...";
        while (!mystack.empty())
        {
            std::cout << ' ' << mystack.top();
            mystack.pop();
        }
        std::cout << '\n';

        std::cout << " -------------------------- \n\n" << std::endl;
    }


    {
        std::cout << " _________________ Testing relational operators _____________________ \n"
                  << std::endl;

        NS::vector<int> foo(3, 100); // three ints with a value of 100
        NS::vector<int> bar(2, 200); // two ints with a value of 200

        NS::stack<int, NS::vector<int> > s1(foo);
        NS::stack<int, NS::vector<int> > s2(bar);

        if (s1 == s2)
            std::cout << "s1 and s2 are equal\n";
        if (s1 != s2)
            std::cout << "s1 and s2 are not equal\n";
        if (s1 < s2)
            std::cout << "s1 is less than s2\n";
        if (s1 > s2)
            std::cout << "s1 is greater than s2\n";
        if (s1 <= s2)
            std::cout << "s1 is less than or equal to s2\n";
        if (s1 >= s2)
            std::cout << "s1 is greater than or equal to s2\n";
        std::cout << " -------------------------- \n\n"
                  << std::endl;
    }

    return 0;
}