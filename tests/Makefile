##
## EPITECH PROJECT, 2017
## Makefile for UT
## File description:
## UT for 42sh
##

SRC_DIR		=	$(realpath ../src)

PARSING_DIR	=	parsing/
SHELL_DIR	=	shell/
BI_DIR		=	$(SHELL_DIR)builtins/
RED_DIR		=	$(SHELL_DIR)redirections/
42RC_DIR	=	$(SHELL_DIR)42rc/
VAR_DIR		=	$(SHELL_DIR)shell_var/
ALIAS_DIR	=	$(SHELL_DIR)alias/
PROMPT_DIR	=	$(SHELL_DIR)prompt/
EXEC_DIR	=	$(SHELL_DIR)exec/
JOBS_DIR	=	$(SHELL_DIR)jobs/

SRC_FILES	=	$(SHELL_DIR)shell.c\
			$(SHELL_DIR)utils.c\
			$(SHELL_DIR)search.c\
			$(SHELL_DIR)debug.c\
			$(SHELL_DIR)init.c\
			$(SHELL_DIR)commands.c\
			$(SHELL_DIR)display.c\
			$(SHELL_DIR)redir.c\
			$(SHELL_DIR)pipe.c\
\
			$(BI_DIR)basic_bi.c\
			$(BI_DIR)env.c\
			$(BI_DIR)repeat.c\
			$(BI_DIR)cd.c\
			$(BI_DIR)history.c\
			$(BI_DIR)history_exec.c\
			$(BI_DIR)fg.c\
			$(BI_DIR)ptr_jobs.c\
			$(BI_DIR)alias.c\
			$(BI_DIR)echo.c\
\
			$(RED_DIR)d_left.c\
			$(RED_DIR)s_left.c\
			$(RED_DIR)d_right.c\
			$(RED_DIR)s_right.c\
\
			$(42RC_DIR)load42.c\
\
			$(VAR_DIR)var.c\
			$(VAR_DIR)var_edition.c\
			$(VAR_DIR)var_utils.c\
\
			$(ALIAS_DIR)alias_struc.c\
			$(ALIAS_DIR)alias_comm.c\
\
			$(PROMPT_DIR)display.c\
			$(PROMPT_DIR)handler_basic.c\
			$(PROMPT_DIR)handler_colors.c\
			$(PROMPT_DIR)handler_time.c\
			$(PROMPT_DIR)system_get.c\
			$(PROMPT_DIR)handler_vars.c\
			$(PROMPT_DIR)handler_date.c\
			$(PROMPT_DIR)handler_get_from_shell.c\
\
			$(PARSING_DIR)parsing.c\
			$(PARSING_DIR)struct.c\
			$(PARSING_DIR)quote.c\
			$(PARSING_DIR)is_quote.c\
			$(PARSING_DIR)split.c\
			$(PARSING_DIR)parentheses.c\
			$(PARSING_DIR)globbing.c\
			$(PARSING_DIR)cmd_separators.c\
			$(PARSING_DIR)browse_node.c\
			$(PARSING_DIR)is_cmd_separator.c\
			$(PARSING_DIR)free_node.c\
			$(PARSING_DIR)init_comm_array.c\
			$(PARSING_DIR)convert_node.c\
			$(PARSING_DIR)handle_separators.c\
\
			$(EXEC_DIR)exec_pipe.c\
			$(EXEC_DIR)redir_pipe.c\
			$(EXEC_DIR)exec.c\
			$(EXEC_DIR)run_bin.c\
\
			$(JOBS_DIR)init_signal.c\
			$(JOBS_DIR)jobs.c\
			$(JOBS_DIR)signals.c\
			$(JOBS_DIR)sig_handlers.c\

SRC		=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

TESTS_DIR	=	$(realpath ./UT)

TESTS_FILES	=	shell_functions_test.c\
			is_quote_functions_test.c\
			struct_functions_test.c\

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