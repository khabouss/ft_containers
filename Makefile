NAME = tester
FLAGS = -Wall -Wextra -Werror -std=c++98
SRC = test/main.cpp 
CPP = c++
M = upload

OBJS	= $(SRC:.cpp=.o)
all: $(NAME)

$(NAME) : $(OBJS)
	$(CPP) $(FLAGS) $(OBJS) -o $(NAME)

.cpp.o:
	$(CPP) $(FLAGS) -c $< -o $(OBJS)

re: fclean $(NAME)
	@clear && ./$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

push: fclean $(NAME)
	@git add *
	@git status
	@git commit -m "$(M)"
	@git push

.PHONY: all re clean fclean push