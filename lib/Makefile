##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

LIBSDIR	=	SFML	\
			SDL2	\
			Libcaca	\
			Ncurses

MAKE	= make --no-print-directory

all: $(LIBSDIR)
	@$(foreach lib,$(LIBSDIR),$(MAKE) -C $(lib) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)" || exit;)

clean: $(LIBSDIR)
	@$(foreach lib,$(LIBSDIR),$(MAKE) clean -C $(lib) || exit;)

fclean: $(LIBSDIR)
	@$(foreach lib,$(LIBSDIR),$(MAKE) fclean -C $(lib) || exit;)

re: fclean all

.PHONY: all clean fclean re