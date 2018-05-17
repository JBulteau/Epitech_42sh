##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Compile our projects
##

NAME		=	42sh

SRC_DIR		=	$(realpath ./src)

SHELL_DIR	=	shell/
BI_DIR		=	$(SHELL_DIR)builtins/
RED_DIR		=	$(SHELL_DIR)redirections/
42RC_DIR	=	$(SHELL_DIR)42rc/
PARSING_DIR	=	$(SHELL_DIR)parsing/

SRC_FILES	=	$(SHELL_DIR)main.c	\
			$(SHELL_DIR)shell.c\
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
			$(BI_DIR)history.c\
\
			$(RED_DIR)d_left.c\
			$(RED_DIR)s_left.c\
			$(RED_DIR)d_right.c\
			$(RED_DIR)s_right.c\
			$(RED_DIR)pipe.c\
\
			$(42RC_DIR)load42.c\
\
			$(PARSING_DIR)parsing.c\
			$(PARSING_DIR)struct.c\
			$(PARSING_DIR)quote.c\
			$(PARSING_DIR)is_quote.c\
			$(PARSING_DIR)split.c\
			$(PARSING_DIR)parentheses.c\
			$(PARSING_DIR)globbing.c\
			$(PARSING_DIR)cmd_separators.c\
			$(PARSING_DIR)is_cmd_separator.c\
			$(PARSING_DIR)free_node.c\

SRC		=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

TEST_FOLDER	=	tests

CFLAGS		=	-W -Wextra -Wall -Wshadow -I include

OBJ		=	$(SRC:%.c=%.o)

LIB_DIR		=	$(realpath ./lib)

LDFLAGS		=	-L $(LIB_DIR) -Llib -lmy

CC		=	gcc

all:		$(NAME)

$(NAME):	$(OBJ)
		$(MAKE) -C $(LIB_DIR)/my
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(CFLAGS)

clean:
		$(RM) $(OBJ)
		$(MAKE) clean -C $(LIB_DIR)/my

fclean:		clean
		$(RM) $(NAME)
		$(MAKE) fclean -C $(LIB_DIR)/my

re:		fclean all

debug:		CFLAGS += -g
debug:		re

tests_run:
		$(MAKE) -C $(TEST_FOLDER)
		./$(TEST_FOLDER)/test > /dev/null

tests_fclean:
		$(MAKE) fclean -C $(TEST_FOLDER)
