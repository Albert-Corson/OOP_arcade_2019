##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

CC	=	g++

SRC	=	src/GameMenu.cpp			\
		src/lib_communs.cpp			\
		src/class/scene/Prompt.cpp	\
		src/class/scene/Menu.cpp

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS	=	$(COMMON_CXXFLAGS)
CXXFLAGS	+=	-fPIC
CXXFLAGS	+=	-I../ -I../games/ -Iinclude/

NAME	=	lib_arcade_menu.so

$(NAME): $(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re