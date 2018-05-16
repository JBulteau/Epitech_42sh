##
## EPITECH PROJECT, 2017
## Makefile for UT
## File description:
## UT for 42sh
##

SRC_DIR		=	$(realpath ../src)

SHELL_DIR	=	shell/
BI_DIR		=	$(SHELL_DIR)builtins/
RED_DIR		=	$(SHELL_DIR)redirections/

SRC_FILES	=	$(SHELL_DIR)shell.c\
			$(SHELL_DIR)utils.c\
			$(SHELL_DIR)search.c\
			$(SHELL_DIR)exec.c\
			$(SHELL_DIR)debug.c\
			$(SHELL_DIR)parsing.c\
			$(SHELL_DIR)commands.c\
			$(SHELL_DIR)display.c\
			$(SHELL_DIR)redir.c\
			$(SHELL_DIR)pipe.c\
\
			$(BI_DIR)basic_bi.c\
			$(BI_DIR)env.c\
			$(BI_DIR)cd.c\
\
			$(RED_DIR)d_left.c\
			$(RED_DIR)s_left.c\
			$(RED_DIR)d_right.c\
			$(RED_DIR)s_right.c\
			$(RED_DIR)pipe.c\

SRC		=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

TESTS_DIR	=	$(realpath ./UT)

TESTS_FILES	=	shell.c

SRC_TESTS	=	$(addprefix $(TESTS_DIR)/, $(TESTS_FILES))

OBJ		=	$(SRC:%.c=%.o) $(SRC_TESTS:%.c=%.o)

CCTMP		=	$(SRC:%.c=%.gcno) $(SRC:%.c=%.gcda) $(SRC_TESTS:%.c=%.gcno) $(SRC_TESTS:%.c=%.gcda)

NAME		=	test

INCLUDE		=	-I ../include

CFLAGS		=	-Wall -Wextra -coverage
CFLAGS		+=	$(INCLUDE)

LIB_DIR		=	../lib/

LIB_FLAGS	=	-L $(LIB_DIR) -lmy -lcriterion -lgcov

LIB		=	$(LIB_DIR)my/libmy.a

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