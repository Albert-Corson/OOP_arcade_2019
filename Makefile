##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

ROOT	:=	$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

COMMON_CXXFLAGS	=	-std=c++17				\
					-Wall					\
					-Wextra					\
					-Wshadow				\
					-Wsign-compare			\
					-Wno-unused-parameter	\
					-Wno-unused-variable	\
					-I$(ROOT)

DEBUG			=	-g

MAKE			=	@make --no-print-directory
COREDIR			=	core
GAMESDIR		=	games
LIBSDIR			=	lib

all: games graphicals core

core:
	$(MAKE) -C $(COREDIR) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)"

games:
	$(MAKE) -C $(GAMESDIR) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)"

graphicals:
	$(MAKE) -C $(LIBSDIR) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)"

clean:
	$(MAKE) clean -C $(COREDIR)
	$(MAKE) clean -C $(GAMESDIR)
	$(MAKE) clean -C $(LIBSDIR)

fclean: clean
	$(MAKE) fclean -C $(COREDIR)
	$(MAKE) fclean -C $(GAMESDIR)
	$(MAKE) fclean -C $(LIBSDIR)

re: fclean all

debug:
	$(MAKE) all COMMON_CXXFLAGS="$(COMMON_CXXFLAGS) $(DEBUG)"

.PHONY: all clean fclean re core graphicals games debug