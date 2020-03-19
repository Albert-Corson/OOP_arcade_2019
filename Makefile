##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

CC				=	g++

COMMON_CXXFLAGS	+=	-std=c++14				\
					-Wall					\
					-Wextra					\
					-Wshadow				\
					-Wsign-compare			\
					-Wno-unused-parameter	\
					-Wno-unused-variable	\

DEBUG			=	-g

CXXFLAGS		=	$(COMMON_CXXFLAGS)

CORE			=	@make --no-print-directory -C core
GAMES			=	@make --no-print-directory -C games
GRAPHICALS		=	@make --no-print-directory -C lib

all: games graphicals core

core:
	$(CORE) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)"

games:
	$(GAMES) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)"

graphicals:
	$(GRAPHICALS) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)"

clean:
	$(GAMES) clean
	$(GRAPHICALS) clean
	$(CORE) clean

fclean: clean
	$(GAMES) fclean
	$(GRAPHICALS) fclean
	$(CORE) fclean

re: fclean all

debug:
	make all COMMON_CXXFLAGS="$(COMMON_CXXFLAGS) $(DEBUG)"

.PHONY: all clean fclean re core graphicals games debug