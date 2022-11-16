NAME = a.out
CPP = c++ 
FLAGS = --std=c++98 -Wall -Wextra -Werror
SRC1 = vector.cpp 
SRC2 = map.cpp 
SRC3 = stack.cpp

OBJS1	= $(SRC1:.cpp=.o)
OBJS2	= $(SRC2:.cpp=.o)
OBJS3	= $(SRC3:.cpp=.o)

vector: $(OBJS1)
	$(CPP) $(FLAGS) $(OBJS1) -o $(NAME)

map: $(OBJS2)
	$(CPP) $(FLAGS) $(OBJS2) -o $(NAME)

stack: $(OBJS3)
	$(CPP) $(FLAGS) $(OBJS3) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

.PHONY: vector map stack clean fclean
