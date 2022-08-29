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

    vec.push_back(10);
    vec.push_back(20);
    
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << std::endl;

    return 0;
}