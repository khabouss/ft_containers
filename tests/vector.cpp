#include "../src/vector/vector.hpp"
#include "../src/map/map.hpp"
#include "../src/stack/stack.hpp"
#include "../src/utils/headers.hpp"

#if 0
    # define NS ft
#else
    #include <vector>
    # define NS std
#endif

template <class T>
void printVector(NS::vector<T> v) {
    for (typename NS::vector<T>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << std::endl;
}

int main(void)
{
    NS::vector<int> first;                               // empty vector of ints
    NS::vector<int> second(4, 100);                      // four ints with value 100
    NS::vector<int> third(second.begin(), second.end()); // iterating through second
    NS::vector<int> fourth(third);                       // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int myint[] = {16,2,77,29};
    NS::vector<int> fifth (myint, myint + sizeof(myint) / sizeof(int) );

    std::cout << " _________________ Testing Constructors _____________________ \n" << std::endl;
    std::cout << "The contents of first are:";
    printVector(first);
    std::cout << " -------------------------- \n" << std::endl;

    std::cout << "The contents of second are:";
    printVector(second);
    std::cout << " -------------------------- \n" << std::endl;

    std::cout << "The contents of third are:";
    printVector(third);
    std::cout << " -------------------------- \n" << std::endl;

    std::cout << "The contents of fourth are:";
    printVector(fourth);
    std::cout << " -------------------------- \n" << std::endl;

    std::cout << "The contents of fifth are:";
    printVector(fifth);
    std::cout << " -------------------------- \n\n" << std::endl;


    std::cout << " _________________ Testing operator= _____________________ \n" << std::endl;
    NS::vector<int> foo(3, 0);
    NS::vector<int> bar(5, 0);

    bar = foo;
    foo = NS::vector<int>();

    std::cout << "The contents of bar are:";
    printVector(bar);
    std::cout << " -------------------------- \n\n" << std::endl;


    std::cout << " _________________ Testing begin(), rbegin() and end(), rend() _____________________ \n" << std::endl;

    NS::vector<std::string> myvector;
    for (int i = 1; i < 10; i++)
        myvector.push_back(std::to_string(i));

    std::cout << "begin() returned: [" << *(myvector.begin()) << "] " << std::endl;
    std::cout << "rbegin() returned: [" << *(myvector.rbegin()) << "] " << std::endl;
    std::cout << "end() returned: [" << *(myvector.end()) << "] " << std::endl;
    std::cout << "rend() returned: [" << *((myvector.rend())) << "] " << std::endl;
    std::cout << " -------------------------- \n\n" << std::endl;



    std::cout << " _________________ Testing size(), capacity() and max_size() _____________________ \n" << std::endl;
    NS::vector<int> myints;
    std::cout << "0. size: " << myints.size() << '\n';
    std::cout << "0. capacity: " << myints.capacity() << '\n';
    std::cout << "0. max_size: " << myints.max_size() << '\n';

    for (int i = 0; i < 10; i++)
        myints.push_back(i);
    std::cout << "1. size: " << myints.size() << '\n';
    std::cout << "1. capacity: " << myints.capacity() << '\n';
    std::cout << "1. max_size: " << myints.max_size() << '\n';

    myints.insert(myints.end(), 10, 100);
    std::cout << "2. size: " << myints.size() << '\n';
    std::cout << "2. capacity: " << myints.capacity() << '\n';
    std::cout << "2. max_size: " << myints.max_size() << '\n';

    myints.pop_back();
    std::cout << "3. size: " << myints.size() << '\n';
    std::cout << "3. capacity: " << myints.capacity() << '\n';
    std::cout << "3. max_size: " << myints.max_size() << '\n';
    std::cout << " -------------------------- \n\n" << std::endl;


    std::cout << " _________________ Testing resize() _____________________ \n" << std::endl;
    NS::vector<int> v1;

    for (int i = 1; i < 10; i++)
        v1.push_back(i);

    v1.resize(5);
    v1.resize(8, 100);
    v1.resize(12);

    std::cout << "v1 contains:";
    for (size_t i = 0; i < v1.size(); i++)
        std::cout << ' ' << v1[i];
    std::cout << '\n';
    std::cout << " -------------------------- \n\n" << std::endl;


    std::cout << " _________________ Testing empty() _____________________ \n" << std::endl;
    NS::vector<int> v2;
    int sum(0);

    for (int i = 1; i <= 10; i++)
        v2.push_back(i);

    while (!v2.empty())
    {
        sum += v2.back();
        v2.pop_back();
    }

    std::cout << "total: " << sum << '\n';
    std::cout << " -------------------------- \n\n" << std::endl;



    std::cout << " _________________ Testing reserve() _____________________ \n" << std::endl;
    NS::vector<int>::size_type sz;

    NS::vector<int> foo1;
    sz = foo1.capacity();
    std::cout << "making foo1 grow:\n";
    for (int i = 0; i < 100; ++i)
    {
        foo1.push_back(i);
        if (sz != foo1.capacity())
        {
            sz = foo1.capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }

    NS::vector<int> bar1;
    sz = bar1.capacity();
    bar1.reserve(100); // this is the only difference with foo1 above
    std::cout << "making bar1 grow:\n";
    for (int i = 0; i < 100; ++i)
    {
        bar1.push_back(i);
        if (sz != bar1.capacity())
        {
            sz = bar1.capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }
    std::cout << " -------------------------- \n\n" << std::endl;




    {
        std::cout << " _________________ Testing operator[] _____________________ \n"
                  << std::endl;
        NS::vector<int> v3(10); // 10 zero-initialized elements

        NS::vector<int>::size_type sz = v3.size();

        // assign some values:
        for (unsigned i = 0; i < sz; i++)
            v3[i] = i;

        // reverse vector using operator[]:
        for (unsigned i = 0; i < sz / 2; i++)
        {
            int temp;
            temp = v3[sz - 1 - i];
            v3[sz - 1 - i] = v3[i];
            v3[i] = temp;
        }

        std::cout << "v3 contains:";
        for (unsigned i = 0; i < sz; i++)
            std::cout << ' ' << v3[i];
        std::cout << '\n';
        std::cout << " -------------------------- \n\n"
                  << std::endl;
    }

    {
        std::cout << " _________________ Testing at() _____________________ \n"
                  << std::endl;

        NS::vector<int> myvector(10); // 10 zero-initialized ints

        // assign some values:
        for (unsigned i = 0; i < myvector.size(); i++)
            myvector.at(i) = i;

        std::cout << "myvector contains:";
        for (unsigned i = 0; i < myvector.size(); i++)
            std::cout << ' ' << myvector.at(i);
        std::cout << '\n';

        std::cout << " -------------------------- \n\n"
                  << std::endl;
    }

    {
        std::cout << " _________________ Testing front() and back() _____________________ \n"
                  << std::endl;

        NS::vector<int> myvector;

        myvector.push_back(78);
        myvector.push_back(16);

        // now front equals 78, and back 16

        myvector.front() -= myvector.back();

        std::cout << "myvector.front() is now " << myvector.front() << '\n';

        std::cout << " -------------------------- \n\n"
                  << std::endl;
    }

    {
        std::cout << " _________________ Testing assign() _____________________ \n"
                  << std::endl;
        NS::vector<int> first;
        NS::vector<int> second;
        NS::vector<int> third;

        first.assign(7, 100); // 7 ints with a value of 100

        NS::vector<int>::iterator it;
        it = first.begin() + 1;

        second.assign(it, first.end() - 1); // the 5 central values of first

        int myints[] = {1776, 7, 4};
        third.assign(myints, myints + 3); // assigning from array.

        std::cout << "Size of first: " << int(first.size()) << '\n';
        std::cout << "Size of second: " << int(second.size()) << '\n';
        std::cout << "Size of third: " << int(third.size()) << '\n';

        std::cout << " -------------------------- \n\n"
                  << std::endl;
    }

    {
        std::cout << " _________________ Testing insert() _____________________ \n"
                  << std::endl;

        NS::vector<int> myvector(3, 100);
        NS::vector<int>::iterator it;

        it = myvector.begin();
        it = myvector.insert(it, 200);

        myvector.insert(it, 2, 300);

        // "it" no longer valid, get a new one:
        it = myvector.begin();

        NS::vector<int> anothervector(2, 400);
        myvector.insert(it + 2, anothervector.begin(), anothervector.end());

        int myarray[] = {501, 502, 503};
        myvector.insert(myvector.begin(), myarray, myarray + 3);

        std::cout << "myvector contains:";
        for (it = myvector.begin(); it < myvector.end(); it++)
            std::cout << ' ' << *it;
        std::cout << '\n';
        std::cout << " -------------------------- \n\n"
                  << std::endl;
    }

    {
        std::cout << " _________________ Testing erase() _____________________ \n"
                  << std::endl;

        NS::vector<int> myvector;

        // set some values (from 1 to 10)
        for (int i = 1; i <= 10; i++)
            myvector.push_back(i);

        // erase the 6th element
        myvector.erase(myvector.begin() + 5);

        // erase the first 3 elements:
        myvector.erase(myvector.begin(), myvector.begin() + 3);

        std::cout << "myvector contains:";
        for (unsigned i = 0; i < myvector.size(); ++i)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';

        std::cout << " -------------------------- \n\n"
                  << std::endl;
    }

    {
        std::cout << " _________________ Testing swap() _____________________ \n"
                  << std::endl;

        NS::vector<int> foo(3, 100); // three ints with a value of 100
        NS::vector<int> bar(5, 200); // five ints with a value of 200

        foo.swap(bar);

        std::cout << "foo contains:";
        for (unsigned i = 0; i < foo.size(); i++)
            std::cout << ' ' << foo[i];
        std::cout << '\n';

        std::cout << "bar contains:";
        for (unsigned i = 0; i < bar.size(); i++)
            std::cout << ' ' << bar[i];
        std::cout << '\n';
        std::cout << " -------------------------- \n\n"
                  << std::endl;
    }

    {
        std::cout << " _________________ Testing clear() _____________________ \n"
                  << std::endl;

        NS::vector<int> myvector;
        myvector.push_back(100);
        myvector.push_back(200);
        myvector.push_back(300);

        std::cout << "myvector contains:";
        for (unsigned i = 0; i < myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';

        myvector.clear();
        myvector.push_back(1101);
        myvector.push_back(2202);

        std::cout << "myvector contains:";
        for (unsigned i = 0; i < myvector.size(); i++)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
        std::cout << " -------------------------- \n\n"
                  << std::endl;
    }

    {
        std::cout << " _________________ Testing get_allocator() _____________________ \n"
                  << std::endl;

        NS::vector<int> myvector;
        int *p;
        unsigned int i;

        // allocate an array with space for 5 elements using vector's allocator:
        p = myvector.get_allocator().allocate(5);

        // construct values in-place on the array:
        for (i = 0; i < 5; i++)
            myvector.get_allocator().construct(&p[i], i);

        std::cout << "The allocated array contains:";
        for (i = 0; i < 5; i++)
            std::cout << ' ' << p[i];
        std::cout << '\n';

        // destroy and deallocate:
        for (i = 0; i < 5; i++)
            myvector.get_allocator().destroy(&p[i]);
        myvector.get_allocator().deallocate(p, 5);
        std::cout << " -------------------------- \n\n"
                  << std::endl;
    }

    {
        std::cout << " _________________ Testing relational operators _____________________ \n"
                  << std::endl;

        NS::vector<int> foo(3, 100); // three ints with a value of 100
        NS::vector<int> bar(2, 200); // two ints with a value of 200

        if (foo == bar)
            std::cout << "foo and bar are equal\n";
        if (foo != bar)
            std::cout << "foo and bar are not equal\n";
        if (foo < bar)
            std::cout << "foo is less than bar\n";
        if (foo > bar)
            std::cout << "foo is greater than bar\n";
        if (foo <= bar)
            std::cout << "foo is less than or equal to bar\n";
        if (foo >= bar)
            std::cout << "foo is greater than or equal to bar\n";
        std::cout << " -------------------------- \n\n"
                  << std::endl;
    }

    // while(1);
    return 0;
}