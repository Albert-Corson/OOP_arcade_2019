##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

GAMESDIR	=	Nibbler		\
				Snake		\
				Pacman		\
				Solarfox

all:
	@$(foreach gamedir,$(GAMESDIR),make -C $(gamedir) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)" || exit;)

clean:
	@$(foreach gamedir,$(GAMESDIR),make clean -C $(gamedir) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)" || exit;)

fclean:
	@$(foreach gamedir,$(GAMESDIR),make fclean -C $(gamedir) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)" || exit;)

re: fclean all

.PHONY: all clean fclean re