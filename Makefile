##
## EPITECH PROJECT, 2021
## MAKEFILE
## File description:
## My supra makefilator
##

LIBS = net json list myteams aes

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
# ================================== RULES ================================== #
# =========================================================================== #

# build
all:
	@$(MAKE) -s make_libs
	@$(MAKE) --no-print-directory -f Makefile_myteams_cli all
	@$(MAKE) --no-print-directory -f Makefile_myteams_server all
.PHONY: all

cli:
	@$(MAKE) -s make_libs
	@$(MAKE) --no-print-directory -f Makefile_myteams_cli all
.PHONY: cli

server:
	@$(MAKE) -s make_libs
	@$(MAKE) --no-print-directory -f Makefile_myteams_server all
.PHONY: server

re:
	@$(MAKE) -s fclean
	@$(MAKE) --no-print-directory all
.PHONY: re

# debug
debug:
	@$(MAKE) make_debug_libs
	@$(MAKE) -f Makefile_myteams_cli debug
	@$(MAKE) -f Makefile_myteams_server debug
.PHONY: debug

# tests
tests_run:
	@$(MAKE) -s make_libs
	@$(MAKE) --no-print-directory -f Makefile_myteams_cli tests_run
	@$(MAKE) --no-print-directory -f Makefile_myteams_server tests_run
	@$(ECHO) "$(OK_STRING) myteams_cli/run unit_tests-myteams_cli"
	@LD_LIBRARY_PATH=$(realpath ./libs) ./unit_tests-myteams_cli 2>&1 | grep -v "overwriting an existing profile data with a different timestamp" || true
	@$(ECHO) "$(OK_STRING) myteams_server/run unit_tests-myteams_server"
	@LD_LIBRARY_PATH=$(realpath ./libs) ./unit_tests-myteams_server 2>&1 | grep -v "overwriting an existing profile data with a different timestamp" || true
.PHONY: tests_run

functional_tests_run:
	@$(MAKE) -s make_libs
	@$(MAKE) --no-print-directory -f Makefile_myteams_cli functional_tests_run
	@$(MAKE) --no-print-directory -f Makefile_myteams_server functional_tests_run
.PHONY: functional_tests_run

# coverage
coverage:
	@$(MAKE) -s tests_run
	@gcovr --exclude tests/ --branch 2> /dev/null
	@gcovr --exclude tests/ 2> /dev/null
.PHONY: coverage

# clean
clean: clean_libs
	@$(MAKE) -s -f Makefile_myteams_cli clean
	@$(MAKE) -s -f Makefile_myteams_server clean
.PHONY: clean

fclean: fclean_libs
	@$(MAKE) -s -f Makefile_myteams_cli fclean
	@$(MAKE) -s -f Makefile_myteams_server fclean
.PHONY: fclean

full_clean: fclean
	@echo -e "\x1b[32;01m[✔]\x1b[0m full_clean"
	@find . -name "*a.out" -delete
	@find . -name "*.o" -delete
	@find . -name "*.d" -delete
	@find . -name "*.a" -delete
	@find . -name "*.so" ! -wholename "./libs/myteams/libmyteams.so" -delete
	@find . -name "*.gch" -delete
	@find . -name "*.gcov" -delete
	@find . -name "*.gcda" -delete
	@find . -name "*.gcno" -delete
	@find . -name "vgcore.*" -delete
	@find . -name "*.c.tmp" -delete
	@find . -name "*.h.tmp" -delete
	@find . -maxdepth 1 -name "*.json" -delete
.PHONY: full_clean

# libs
make_libs:
	@for i in $(LIBS); do \
		(cd libs/$$i/ && $(MAKE) -s all); \
	done

make_debug_libs:
	@for i in $(LIBS); do \
		(cd libs/$$i/ && $(MAKE) debug); \
	done

clean_libs:
	@for i in $(LIBS); do \
		(cd libs/$$i/ && $(MAKE) -s clean); \
	done

fclean_libs:
	@for i in $(LIBS); do \
		(cd libs/$$i/ && $(MAKE) -s fclean); \
	done