
COMPILER = c++
FLAGS_DEBUG = --std=c++98 -Wall -Wextra -Werror -fsanitize=address -g3
FLAGS = --std=c++98 -Wall -Wextra -Werror -g

vector:
	@$(COMPILER) $(FLAGS)	vector.cpp -o vector.out 

map:
	@$(COMPILER) $(FLAGS)	Map_tests.cpp -o map.out 

stack:
	@$(COMPILER) $(FLAGS)	Stack_tests.cpp -o stack.out 

set:
	@$(COMPILER) $(FLAGS)	Set_tests.cpp -o set.out 
clean:
	rm -f vector.out map.out stack.out set.out
