##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Compile our projects
##

NAME		=	42sh

TESTS_DIR	=	$(realpath ./tests)

SRC_DIR		=	$(realpath ./src)

SHELL_DIR	=	shell/
BI_DIR		=	$(SHELL_DIR)builtins/
RED_DIR		=	$(SHELL_DIR)redirections/
42RC_DIR	=	$(SHELL_DIR)42rc/
VAR_DIR		=	$(SHELL_DIR)shell_var/
ALIAS_DIR	=	$(SHELL_DIR)alias/

SRC_FILES	=	$(SHELL_DIR)main.c\
			$(SHELL_DIR)shell.c\
			$(SHELL_DIR)utils.c\
			$(SHELL_DIR)search.c\
			$(SHELL_DIR)exec.c\
			$(SHELL_DIR)debug.c\
			$(SHELL_DIR)parsing.c\
			$(SHELL_DIR)infos.c\
			$(SHELL_DIR)commands.c\
			$(SHELL_DIR)display.c\
			$(SHELL_DIR)redir.c\
			$(SHELL_DIR)pipe.c\
			$(SHELL_DIR)exec_pipe.c\
			$(SHELL_DIR)redir_pipe.c\
			$(SHELL_DIR)init_signal.c\
			$(SHELL_DIR)jobs.c\
\
			$(BI_DIR)basic_bi.c\
			$(BI_DIR)env.c\
			$(BI_DIR)cd.c\
			$(BI_DIR)history.c\
			$(BI_DIR)history_exec.c\
			$(BI_DIR)fg.c\
			$(BI_DIR)alias.c\
			$(BI_DIR)echo.c\
\
			$(RED_DIR)d_left.c\
			$(RED_DIR)s_left.c\
			$(RED_DIR)d_right.c\
			$(RED_DIR)s_right.c\
			$(RED_DIR)pipe.c\
\
			$(42RC_DIR)load42.c\
\
			$(VAR_DIR)var.c\
			$(VAR_DIR)var_edition.c\
			$(VAR_DIR)var_utils.c\
\
			$(ALIAS_DIR)alias_struc.c\
			$(ALIAS_DIR)alias_comm.c\

SRC		=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

CFLAGS		=	-W -Wextra  -I include -Wall -Wshadow

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