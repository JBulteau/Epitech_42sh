##
## EPITECH PROJECT, 2017
## Makefile for UT
## File description:
## UT for lib
##

SRC_DIR		=	$(realpath ..)

SRC_FILES	=	check_str.c\
			maths.c\
			my_put.c\
			my_str.c\
			my_str2.c\
			parsing.c\
			my_array.c\
			my_get.c\
			gnl.c\

SRC		=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

TESTS_DIR	=	$(realpath .)

TESTS_FILES	=	tests_check_str.c\
			tests_maths.c\
			tests_my_put.c\
			tests_my_str.c\
			tests_my_str2.c\
			tests_parsing.c\
			tests_my_array.c\
			tests_my_get.c\
			tests_gnl.c\

SRC_TESTS	=	$(addprefix $(TESTS_DIR)/, $(TESTS_FILES))

OBJ		=	$(SRC:%.c=%.o) $(SRC_TESTS:%.c=%.o)

CCTMP		=	$(SRC:%.c=%.gcno) $(SRC:%.c=%.gcda) $(SRC_TESTS:%.c=%.gcno) $(SRC_TESTS:%.c=%.gcda)

NAME		=	test

INCLUDE		=	-I ../../../include

CFLAGS		=	-Wall -Wextra -coverage
CFLAGS		+=	$(INCLUDE)

LIB_FLAGS	=	-lcriterion -lgcov

CC		=	gcc

all:		$(NAME)

$(NAME):	$(LIB)
		$(CC) -o $(NAME) $(SRC) $(SRC_TESTS) $(LIB_FLAGS) $(CFLAGS)

$(LIB):
		$(MAKE) -C $(LIB_DIR)my
		$(MAKE) clean -C $(LIB_DIR)my

cclean:
		$(RM) $(CCTMP)
		$(RM) *.gcno
		$(RM) *.gcda
		$(RM) *.gcov

clean:		cclean
		$(RM) $(OBJ)

fclean:		clean
		$(RM) -f $(NAME)

re:		fclean all