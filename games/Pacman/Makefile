##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

CC	=	g++

SRC	=	

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS	=	$(COMMON_CXXFLAGS)
CXXFLAGS	+=

NAME	=	

$(NAME): $(OBJ)
	g++ -shared -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re