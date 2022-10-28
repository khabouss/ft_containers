#include <vector>
#include <iostream>
#include <iterator>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
// #include "../src/map/map.hpp"
#include "../src/map/avl_tree.hpp"
#include <iterator>
#include <type_traits>
#include <stack>
#include "../src/pair/pair.hpp"

int main() {
    avl_tree< ft::pair<int,int> > tree;
    tree.root = tree.insertNode(tree.root, ft::make_pair<int, int>(33, 33));
    tree.insertNode(tree.root, ft::make_pair<int, int>(13, 13));
    tree.insertNode(tree.root, ft::make_pair<int, int>(53, 53));
    tree.insertNode(tree.root, ft::make_pair<int, int>(9, 9));
    tree.insertNode(tree.root, ft::make_pair<int, int>(21, 21));
    tree.insertNode(tree.root, ft::make_pair<int, int>(61, 61));
    tree.insertNode(tree.root, ft::make_pair<int, int>(8, 8));
    tree.insertNode(tree.root, ft::make_pair<int, int>(11, 11));
    tree.printTree(tree.root, "", true);
    tree.deleteNode(tree.root, ft::make_pair<int, int>(13, 13));
    std::cout << "After deleting " << std::endl;
    tree.printTree(tree.root, "", true);
    return 0;
}