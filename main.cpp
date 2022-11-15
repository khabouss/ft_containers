#include "src/map/map.hpp"       // your Map path.
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


int main() {


    {
        ft::map<int, std::string> ft_m;
        std::map<int, std::string> m;

        for (int i=0; i < 21; i++) {
            m.insert(std::make_pair(i, "s"));
            ft_m.insert(ft::make_pair(i, "s"));
        }

        int deletes[] = {0, 11, 20, 17, 11, 1, 6, 12, 1, 15, 5};

        std::cout << "before deleting" << std::endl;
        ft_m.printHelper(ft_m.getRoot(), "", true);

        for (int i = 0; i < 11; i++)
        {
            m.erase(deletes[i]);
            ft_m.erase(deletes[i]);
            // std::cout << "after deleting" << std::endl;
            // std::cout << " ---------------------------------- " << std::endl;
            // ft_m.printHelper(ft_m.getRoot(), "", true);        
            // std::cout << " ---------------------------------- " << std::endl;
        }
            // exit (0);

        std::cout << "after deleting" << std::endl;
        ft_m.printHelper(ft_m.getRoot(), "", true);

        m.erase(m.begin(), m.end());
        ft_m.erase(ft_m.begin(), ft_m.end());
        
    }

    return 0;
}