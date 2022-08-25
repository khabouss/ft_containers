#include "../src/vector/vector.hpp"

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

int main()
{
    ft::vector<int> vec;

    for (int i = 0; i < 2; i++)
        vec.push_back(i);
    for (int i = 0; i < 2; i++)
        std::cout << vec[i] << std::endl;

    return 0;
}