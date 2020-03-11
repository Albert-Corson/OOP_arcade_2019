##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

SRC	=	core/main.cpp

OBJ	=	$(SRC:.cpp=.o)

COMMON_CXXFLAGS	+=	-std=c++14				\
					-Wall					\
					-Wextra					\
					-Wshadow				\
					-Wsign-compare			\
					-Wno-unused-parameter	\
					-Wno-unused-variable

DEBUG	=	-g

CXXFLAGS	=	$(COMMON_CXXFLAGS)

NAME	=	arcade

ROOT	=	$(abspath $(lastword $(MAKEFILE_LIST)))

GAMES	=	make -C games
GRAPHICALS	=	make -C lib

all: games graphicals core

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ)

core: $(NAME)

games:
	$(GAMES) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)"

graphicals:
	$(GRAPHICALS) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)"

clean:
	$(GAMES) clean
	$(GRAPHICALS) clean
	rm -rf $(OBJ)

fclean: clean
	$(GAMES) fclean
	$(GRAPHICALS) fclean
	rm -rf $(NAME)

re: fclean all

debug:
	make all COMMON_CXXFLAGS="$(COMMON_CXXFLAGS) $(DEBUG)"

.PHONY: all clean fclean re core graphicals games