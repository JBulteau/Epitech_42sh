##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Compile our projects
##

NAME		=	42sh

TESTS_DIR	=	$(realpath ./tests)

SRC_DIR		=	$(realpath ./src)

PARSING_DIR	=	parsing/
JARVIS_DIR	=	jarvis/
SHELL_DIR	=	shell/
BI_DIR		=	$(SHELL_DIR)builtins/
RED_DIR		=	$(SHELL_DIR)redirections/
42RC_DIR	=	$(SHELL_DIR)42rc/
VAR_DIR		=	$(SHELL_DIR)shell_var/
ALIAS_DIR	=	$(SHELL_DIR)alias/
PROMPT_DIR	=	$(SHELL_DIR)prompt/
EXEC_DIR	=	$(SHELL_DIR)exec/
JOBS_DIR	=	$(SHELL_DIR)jobs/

SRC_FILES	=	$(SHELL_DIR)main.c\
			$(SHELL_DIR)shell.c\
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
			$(BI_DIR)dirs.c\
			$(BI_DIR)fouchauve.c\
			$(BI_DIR)vars.c\
			$(BI_DIR)printenv.c\
			$(BI_DIR)source.c\
			$(BI_DIR)which_where.c\
\
			$(RED_DIR)d_left.c\
			$(RED_DIR)s_left.c\
			$(RED_DIR)d_right.c\
			$(RED_DIR)s_right.c\
			$(RED_DIR)magic_quotes.c\
\
			$(42RC_DIR)load_shell_rc.c\
\
			$(VAR_DIR)var.c\
			$(VAR_DIR)var_ptr_base.c\
			$(VAR_DIR)var_ptr_next.c\
			$(VAR_DIR)var_edition.c\
			$(VAR_DIR)var_operations.c\
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
			$(PARSING_DIR)handle_aliases.c\
			$(PARSING_DIR)convert_utils.c\
			$(PARSING_DIR)separators.c\
			$(PARSING_DIR)search_aliases.c\
			$(PARSING_DIR)handle_variables.c\
			$(PARSING_DIR)replace_variables.c\
			$(PARSING_DIR)parsing_security.c\
\
			$(EXEC_DIR)exec_pipe.c\
			$(EXEC_DIR)redir_pipe.c\
			$(EXEC_DIR)exec.c\
			$(EXEC_DIR)exec_jarvis.c\
			$(EXEC_DIR)run_bin.c\
\
			$(JOBS_DIR)init_signal.c\
			$(JOBS_DIR)jobs.c\
			$(JOBS_DIR)signals.c\
			$(JOBS_DIR)sig_handlers.c\
\
			$(JARVIS_DIR)disp_modif.c\
			$(JARVIS_DIR)jarvis_corrector.c\
			$(JARVIS_DIR)jarvis_corrector_spaces.c\
			$(JARVIS_DIR)jarvis_corrector_misspell.c\
			$(JARVIS_DIR)jarvis_corrector_tools.c\
			$(JARVIS_DIR)jarvis_corrector_algo.c\
			$(JARVIS_DIR)jarvis_corrector_refill.c\
			$(JARVIS_DIR)jarvis_corrector_misspell_final.c\
			$(JARVIS_DIR)jarvis_corrector_init_jarg.c\
			$(JARVIS_DIR)jarvis_corrector_utils.c\
			$(JARVIS_DIR)jarvis_corrector_algo_short.c\
			$(JARVIS_DIR)jarvis_corrector_short_rm_sub.c\
			$(JARVIS_DIR)jarvis_corrector_algo_loop.c\
			$(JARVIS_DIR)jarvis_corrector_local_command.c\
			$(JARVIS_DIR)jarvis_corrector_no_local.c\
			$(JARVIS_DIR)jarvis_corrector_algo_no_local.c\
			$(JARVIS_DIR)jarvis_corrector_algo_short_no_local.c\
			$(JARVIS_DIR)jarvis_corrector_algo_short_add_rm_no_local.c\
			$(JARVIS_DIR)jarvis_corrector_algo_sub_no_local.c\
			$(JARVIS_DIR)jarvis_corrector_built.c\


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
		$(MAKE) clean -C $(TESTS_DIR)

fclean:		clean
		$(RM) $(NAME)
		$(MAKE) fclean -C $(LIB_DIR)/my
		$(MAKE) fclean -C $(TESTS_DIR)

re:		fclean all

debug:		CFLAGS += -g
debug:		$(OBJ)
		$(MAKE) -C $(LIB_DIR)/my debug
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(CFLAGS)

units:
		$(MAKE) -C $(TESTS_DIR)
		$(TESTS_DIR)/test
tests_run:
		$(MAKE) -C $(TEST_FOLDER)
		./$(TEST_FOLDER)/test > /dev/null

tests_fclean:
		$(MAKE) fclean -C $(TEST_FOLDER)
