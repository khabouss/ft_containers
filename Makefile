NAME = tester
FLAGS = -Wall -Wextra -Werror -std=c++98
SRC = test/main.cpp 
CPP = c++

OBJS	= $(SRC:.cpp=.o)
all: $(NAME)

$(NAME) : $(OBJS)
	$(CPP) $(FLAGS) $(OBJS) -o $(NAME)

.cpp.o:
	$(CPP) $(FLAGS) -c $< -o $(OBJS)

re: fclean $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

.PHONY: all re clean fclean