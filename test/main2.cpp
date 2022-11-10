#include <vector>
#include <iostream>
#include <iterator>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <map>
// #include "../src/map/map.hpp"
#include "../src/map/avl_tree.hpp"
#include "../src/map/map.hpp"
#include <iterator>
#include <type_traits>
#include <stack>
#include "../src/pair/pair.hpp"


int main() {
    {
        ft::map<int, std::string> my_m;
        for (int i = 0; i < 10; ++i)
            my_m.insert(ft::make_pair<int, std::string>(i, (std::string) "fill"));
        // my_m.tree.printTree(my_m.tree.root, "", true);
        // exit(0);
    }
    return 0;
}