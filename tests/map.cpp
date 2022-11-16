#include "../src/vector/vector.hpp"
#include "../src/map/map.hpp"
#include "../src/stack/stack.hpp"
#include "../src/utils/headers.hpp"
#include <memory>

#if 1
    # define NS ft
#else
    #include <map>
    # define NS std
#endif


bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

template <class T, class K>
void printMap(NS::map<T, K> v) {
    for (typename NS::map<T, K>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << " [" << (*it).first << ", " << (*it).second << "] ";
    std::cout << std::endl;
}

int main() {

    {
        std::cout << " _________________ Testing Construct _____________________ \n" << std::endl;
        NS::map<char, int> first;

        first['a'] = 10;
        first['b'] = 30;
        first['c'] = 50;
        first['d'] = 70;

        std::cout << "frst has: ";
        printMap(first);
        std::cout << std::endl;

        NS::map<char, int> second(first.begin(), first.end());
        
        std::cout << "second has: ";
        printMap(second);
        std::cout << std::endl;

        NS::map<char, int> third(second);
        
        std::cout << "third has: ";
        printMap(third);
        std::cout << std::endl;

        std::cout << " -------------------------- \n\n" << std::endl;
    }

    {
        std::cout << " _________________ Testing operator= _____________________ \n" << std::endl;
        NS::map<char, int> first;
        NS::map<char, int> second;

        first['x'] = 8;
        first['y'] = 16;
        first['z'] = 32;

        second = first;                // second now contains 3 ints
        first = NS::map<char, int>(); // and first is now empty

        std::cout << "Size of first: " << first.size() << '\n';
        std::cout << "Size of second: " << second.size() << '\n';

        std::cout << " -------------------------- \n\n" << std::endl;
    }


    {
        std::cout << " _________________ Testing begin, end, rend, rbegin _____________________ \n" << std::endl;
        NS::map<char, int> mymap;

        mymap['b'] = 100;
        mymap['a'] = 200;
        mymap['c'] = 300;
        mymap['w'] = 211;
        mymap['z'] = 333;

        // show content:
        std::cout << "begin(): " << (*(mymap.begin())).first << std::endl;
        std::cout << "rbegin(): " << (*(mymap.rbegin())).first << std::endl;
        std::cout << "end(): " << (*(mymap.end())).first << std::endl;
        std::cout << "rend(): " << (*(mymap.rend())).first << std::endl;

        std::cout << " -------------------------- \n\n" << std::endl;
    }



    {
        std::cout << " _________________ Testing empty, size, max_size _____________________ \n" << std::endl;
        NS::map<char,int> mymap;

        mymap['a'] = 10;
        mymap['b'] = 20;
        mymap['c'] = 30;

        std::cout << "size: " << mymap.size() << std::endl;
        std::cout << "max_size: " << mymap.max_size() << std::endl;

        while (!mymap.empty())
        {
            std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
            mymap.erase(mymap.begin());
        }

        std::cout << " -------------------------- \n\n" << std::endl;
    }



    {
        std::cout << " _________________ Testing operator[] _____________________ \n" << std::endl;
        NS::map<char, std::string> mymap;

        mymap['a'] = "an element";
        mymap['b'] = "another element";
        mymap['c'] = mymap['b'];

        std::cout << "mymap['a'] is " << mymap['a'] << '\n';
        std::cout << "mymap['b'] is " << mymap['b'] << '\n';
        std::cout << "mymap['c'] is " << mymap['c'] << '\n';
        std::cout << "mymap['d'] is " << mymap['d'] << '\n';

        std::cout << "mymap now contains " << mymap.size() << " elements.\n";

        std::cout << " -------------------------- \n\n" << std::endl;
    }


    {
        std::cout << " _________________ Testing insert _____________________ \n" << std::endl;
        NS::map<char, int> mymap;

        // first insert function version (single parameter):
        mymap.insert(NS::pair<char, int>('a', 100));
        mymap.insert(NS::pair<char, int>('z', 200));

        NS::pair<NS::map<char, int>::iterator, bool> ret;
        ret = mymap.insert(NS::pair<char, int>('z', 500));
        if (ret.second == false)
        {
            std::cout << "element 'z' already existed";
            std::cout << " with a value of " << ret.first->second << '\n';
        }

        // second insert function version (with hint position):
        NS::map<char, int>::iterator it = mymap.begin();
        mymap.insert(it, NS::pair<char, int>('b', 300)); 
        mymap.insert(it, NS::pair<char, int>('c', 400)); 

        // third insert function version (range insertion):
        NS::map<char, int> anothermap;
        anothermap.insert(mymap.begin(), mymap.find('c'));

        // showing contents:
        std::cout << "mymap contains:\n";
        for (it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::cout << "anothermap contains:\n";
        for (it = anothermap.begin(); it != anothermap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::cout << " -------------------------- \n\n" << std::endl;
    }


    {
        std::cout << " _________________ Testing erase _____________________ \n" << std::endl;
        NS::map<char, int> mymap;
        NS::map<char, int>::iterator it;

        // insert some values:
        mymap['a'] = 10;
        mymap['b'] = 20;
        mymap['c'] = 30;
        mymap['d'] = 40;
        mymap['e'] = 50;
        mymap['f'] = 60;

        it = mymap.find('b');
        mymap.erase(it); // erasing by iterator

        mymap.erase('c'); // erasing by key

        it = mymap.find('e');
        mymap.erase(it, mymap.end()); // erasing by range

        // show content:
        for (it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::cout << " -------------------------- \n\n" << std::endl;
    }


    {
        std::cout << " _________________ Testing swap _____________________ \n" << std::endl;
        NS::map<char, int> foo, bar;

        foo['x'] = 100;
        foo['y'] = 200;

        bar['a'] = 11;
        bar['b'] = 22;
        bar['c'] = 33;

        foo.swap(bar);

        std::cout << "foo contains:\n";
        for (NS::map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::cout << "bar contains:\n";
        for (NS::map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::cout << " -------------------------- \n\n" << std::endl;
    }


    {
        std::cout << " _________________ Testing clear _____________________ \n" << std::endl;
        NS::map<char, int> mymap;

        mymap['x'] = 100;
        mymap['y'] = 200;
        mymap['z'] = 300;

        std::cout << "mymap contains:\n";
        for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        mymap.clear();
        mymap['a'] = 1101;
        mymap['b'] = 2202;

        std::cout << "mymap contains:\n";
        for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::cout << " -------------------------- \n\n" << std::endl;
    }


    {
        std::cout << " _________________ Testing key_comp _____________________ \n" << std::endl;
        NS::map<char, int> mymap;

        NS::map<char, int>::key_compare mycomp = mymap.key_comp();

        mymap['a'] = 100;
        mymap['b'] = 200;
        mymap['c'] = 300;

        std::cout << "mymap contains:\n";

        char highest = mymap.rbegin()->first; // key value of last element

        NS::map<char, int>::iterator it = mymap.begin();
        do
        {
            std::cout << it->first << " => " << it->second << '\n';
        } while (mycomp((*it++).first, highest));

        std::cout << '\n';

        std::cout << " -------------------------- \n\n" << std::endl;
    }


    {
        std::cout << " _________________ Testing value_comp _____________________ \n" << std::endl;
        NS::map<char, int> mymap;

        mymap['x'] = 1001;
        mymap['y'] = 2002;
        mymap['z'] = 3003;

        std::cout << "mymap contains:\n";

        NS::pair<char, int> highest = *mymap.rbegin(); // last element

        NS::map<char, int>::iterator it = mymap.begin();
        do
        {
            std::cout << it->first << " => " << it->second << '\n';
        } while (mymap.value_comp()(*it++, highest));

        std::cout << " -------------------------- \n\n" << std::endl;
    }


    {
        std::cout << " _________________ Testing find _____________________ \n" << std::endl;
        NS::map<char, int> mymap;
        NS::map<char, int>::iterator it;

        mymap['a'] = 50;
        mymap['b'] = 100;
        mymap['c'] = 150;
        mymap['d'] = 200;

        it = mymap.find('b');
        if (it != mymap.end())
            mymap.erase(it);

        // print content:
        std::cout << "elements in mymap:" << '\n';
        std::cout << "a => " << mymap.find('a')->second << '\n';
        std::cout << "c => " << mymap.find('c')->second << '\n';
        std::cout << "d => " << mymap.find('d')->second << '\n';

        std::cout << " -------------------------- \n\n"
                  << std::endl;
    }

    {
        std::cout << " _________________ Testing count _____________________ \n" << std::endl;
        NS::map<char, int> mymap;
        char c;

        mymap['a'] = 101;
        mymap['c'] = 202;
        mymap['f'] = 303;

        for (c = 'a'; c < 'h'; c++)
        {
            std::cout << c;
            if (mymap.count(c) > 0)
                std::cout << " is an element of mymap.\n";
            else
                std::cout << " is not an element of mymap.\n";
        }

        std::cout << " -------------------------- \n\n" << std::endl;
    }


    {
        std::cout << " _________________ Testing lower_bound _____________________ \n" << std::endl;

        NS::map<char, int> mymap;
        NS::map<char, int>::iterator itlow, itup;

        mymap['a'] = 20;
        mymap['b'] = 40;
        mymap['c'] = 60;
        mymap['d'] = 80;
        mymap['e'] = 100;

        itlow = mymap.lower_bound('b'); // itlow points to b
        itup = mymap.upper_bound('d');  // itup points to e (not d!)

        mymap.erase(itlow, itup); // erases [itlow,itup)

        // print content:
        for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << " -------------------------- \n\n" << std::endl;
    }


    {
        std::cout << " _________________ Testing upper_bound _____________________ \n" << std::endl;
        NS::map<char, int> mymap;
        NS::map<char, int>::iterator itlow, itup;

        mymap['a'] = 20;
        mymap['b'] = 40;
        mymap['c'] = 60;
        mymap['d'] = 80;
        mymap['e'] = 100;

        itlow = mymap.lower_bound('b'); // itlow points to b
        itup = mymap.upper_bound('d');  // itup points to e (not d!)

        mymap.erase(itlow, itup); // erases [itlow,itup)

        // print content:
        for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::cout << " -------------------------- \n\n" << std::endl;
    }



    {
        std::cout << " _________________ Testing equal_range _____________________ \n" << std::endl;
        NS::map<char, int> mymap;

        mymap['a'] = 10;
        mymap['b'] = 20;
        mymap['c'] = 30;

        NS::pair<NS::map<char, int>::iterator, NS::map<char, int>::iterator> ret;
        ret = mymap.equal_range('b');

        std::cout << "lower bound points to: ";
        std::cout << ret.first->first << " => " << ret.first->second << '\n';

        std::cout << "upper bound points to: ";
        std::cout << ret.second->first << " => " << ret.second->second << '\n';

        std::cout << " -------------------------- \n\n" << std::endl;
    }


    {
        std::cout << " _________________ Testing get_allocator _____________________ \n" << std::endl;
        int psize;
        NS::map<char, int> mymap;
        NS::pair<const char, int> *p;

        // allocate an array of 5 elements using mymap's allocator:
        p = mymap.get_allocator().allocate(5);
        // assign some values to array
        psize = sizeof(NS::map<char, int>::value_type) * 5;

        std::cout << "The allocated array has a size of " << psize << " bytes.\n";

        mymap.get_allocator().deallocate(p, 5);

        std::cout << " -------------------------- \n\n" << std::endl;
    }

    return 0;
}