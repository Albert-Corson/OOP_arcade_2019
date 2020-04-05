##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

CC			=	g++

SRC			=	LibGraphLibcaca.cpp	\
				lib_communs.cpp

OBJ			=	$(SRC:.cpp=.o)

CXXFLAGS	=	$(COMMON_CXXFLAGS)
CXXFLAGS	+=	-fPIC			\
				-I../ -I../../

LDLIBS		=	-lcaca

NAME		=	../lib_arcade_libcaca.so

$(NAME): $(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ) $(LDLIBS)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re