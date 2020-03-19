##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

LIBSDIR	=	SFML	\
			Ncurses

all: $(LIBSDIR)
	make -C $< COMMON_CXXFLAGS="$(COMMON_CXXFLAGS) -fPIC -I../"

clean: $(LIBSDIR)
	make -C $< clean

fclean: $(LIBSDIR)
	make -C $< fclean

re: fclean all

.PHONY: all clean fclean re