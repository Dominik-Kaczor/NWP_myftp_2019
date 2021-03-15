##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile for the ex00
##

DIR_TESTS	=	tests/

DIR_SRC		=	src/

CPPFLAGS	=	-I./include -Wall -Wextra

SRC		=	$(DIR_SRC)main.c		\
			$(DIR_SRC)core.c		\
			$(DIR_SRC)error_handling.c	\
			$(DIR_SRC)tools.c		\
			$(DIR_SRC)protocol.c		\
			$(DIR_SRC)loging.c		\
			$(DIR_SRC)info.c		\
			$(DIR_SRC)initialisation.c	\
			$(DIR_SRC)file_command.c	\
			$(DIR_SRC)transfer_params.c

SRC_TESTS	=	$(DIR_TESTS)tests.c

OBJ_TESTS	=	$(DIR_T:.c=.o)

OBJ		=	$(SRC:.c=.o)

NAME		=	myftp

CC		=	gcc

RM		=	rm -f

NAME_TESTS	=	unit_tests

LIB_CRITERION	=	-lcriterion --coverage

%.o: %.c
		@$(CC) $(CPPFLAGS) -c $< -o $@
		@printf "[\033[0;32mCopiled\033[0m] % 30s\n" $< | tr ' ' '.'

all:		$(OBJ)
		@printf "[\033[0;33mBuild\033[0m] % 32s\n" $(NAME) | tr ' ' '.'
		@$(CC) $(CPPFLAGS) -o $(NAME) $(SRC)

tests_run:	fclean $(OBJ_TESTS)
		@$(CC) $(CPPFLAG) $(CPPFLAGS) -o $(NAME_TESTS) $(SRC_TESTS) $(LIB_CRITERION)
		@$(RM) $(OBJ_TESTS)
		@./$(NAME_TESTS) --verbose

clean:
		@printf "[\033[0;31mDeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.'
		@printf "[\033[0;31mDeleted\033[0m] % 30s\n" $(OBJ) | tr ' ' '.'
		@$(RM) $(OBJ)
		@$(RM) $(NAME)

fclean:		clean rm_test

rm_test:	clean
		@$(RM) $(NAME_TESTS)
		@$(RM) *.gcno
		@$(RM) *.gcda

re:		fclean all

debug:		CPPFLAGS	+=	-g3
debug:		re

.PHONY:		all clean tests_run rm_test fclean re debug
