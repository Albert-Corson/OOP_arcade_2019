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
CXXFLAGS	+=	-fPIC	\
				-I../

NAME	=	lib_arcade_Centipede.so

$(NAME): $(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re