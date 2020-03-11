##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

GAMESDIR	=	Centipede	\
				Nibbler		\
				Pacman		\
				Qix			\
				Solarfox

all: $(GAMESDIR)
	make -C $< COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)"

clean: $(GAMESDIR)
	make -C $< clean

fclean: $(GAMESDIR)
	make -C $< fclean

re: fclean all

.PHONY: all clean fclean re