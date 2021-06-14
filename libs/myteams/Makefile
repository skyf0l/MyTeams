##
## EPITECH PROJECT, 2021
## MAKEFILE
## File description:
## My supra makefilator
##

# =========================================================================== #
# =================================== VAR =================================== #
# =========================================================================== #

# binary output
NAME = myteams
LIBNAME = lib$(NAME).so

INCLUDE_DIR = ./

## lib vars
LIB_DEST = ../$(LIBNAME)
HEADERS_DEST = ../../include/libs/$(NAME)/

# =========================================================================== #
# ================================= DISPLAY ================================= #
# =========================================================================== #

## echo
ECHO = echo -e

NO_COLOR = \x1b[0m
OK_COLOR = \x1b[32;01m
ERROR_COLOR = \x1b[31;01m
WARN_COLOR = \x1b[33;01m

OK_STRING = $(OK_COLOR)[✔]$(NO_COLOR)
ERROR_STRING = $(ERROR_COLOR)[X]$(NO_COLOR)
WARN_STRING = $(WARN_COLOR)[!]$(NO_COLOR)

# =========================================================================== #
# ================================== OTHER ================================== #
# =========================================================================== #

RM = rm -f

# =========================================================================== #
# ================================== RULES ================================== #
# =========================================================================== #

all: $(LIB_DEST)
.PHONY: all

$(LIB_DEST):
	@$(ECHO) "lib: $(OK_STRING) $(NAME)/build $(NAME)"
	@cp -f $(LIBNAME) $(LIB_DEST)
	@mkdir -p $(HEADERS_DEST)
	@cp -r $(INCLUDE_DIR)/*.h $(HEADERS_DEST)
	@rm -rf $(HEADERS_DEST)/private

re:
	@$(MAKE) -s fclean
	@$(MAKE) -s all
.PHONY: re

# debug
debug: $(LIB_DEST)
.PHONY: debug

# clean
clean:
	@$(ECHO) "lib: $(OK_STRING) $(NAME)/clean"
.PHONY: clean

fclean: clean
	@$(ECHO) "lib: $(OK_STRING) $(NAME)/fclean"
	@$(RM) $(LIB_DEST)
	@$(RM) -r $(HEADERS_DEST)
.PHONY: fclean

# default target
.DEFAULT_GOAL = all