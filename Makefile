##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Compile our projects
##

NAME		=	42sh

SRC_DIR		=	$(realpath ./src)

JARVIS_DIR	=	jarvis/
SHELL_DIR	=	shell/
BI_DIR		=	$(SHELL_DIR)builtins/
RED_DIR		=	$(SHELL_DIR)redirections/

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
\
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


SRC		=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

CFLAGS		=	-W -Wextra  -I include

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