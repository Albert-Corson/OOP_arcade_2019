##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

LIBSDIR			=	SFML	\
					Ncurses

MAKE			= make --no-print-directory

all: $(LIBSDIR)
	@$(foreach lib,$(LIBSDIR),$(MAKE) -C $(lib) COMMON_CXXFLAGS="$(COMMON_CXXFLAGS)";)

clean: $(LIBSDIR)
	@$(foreach lib,$(LIBSDIR),$(MAKE) clean -C $(lib);)

fclean: $(LIBSDIR)
	@$(foreach lib,$(LIBSDIR),$(MAKE) fclean -C $(lib);)

re: fclean all

.PHONY: all clean fclean re