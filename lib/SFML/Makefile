##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

CC			=	g++

SRC			=	LibGraphSFML.cpp

OBJ			=	$(SRC:.cpp=.o)

CXXFLAGS	=	$(COMMON_CXXFLAGS)
CXXFLAGS	+=	-fPIC	\
				-I../

NAME		=	../lib_arcade_SFML.so

$(NAME): $(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re