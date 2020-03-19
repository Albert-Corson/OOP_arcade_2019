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

all:
	@$(foreach gamedir,$(GAMESDIR),make -C $(gamedir) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)";)

clean:
	@$(foreach gamedir,$(GAMESDIR),make clean -C $(gamedir) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)";)

fclean:
	@$(foreach gamedir,$(GAMESDIR),make fclean -C $(gamedir) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)";)

re: fclean all

.PHONY: all clean fclean re