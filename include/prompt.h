/*
** EPITECH PROJECT, 2017
** builtins.h
** File description:
** builtins for minishell
*/

#ifndef __PROMPT__
#define __PROMPT__

#include "minishell.h"

#define DEBUG_PS1       "PATH [%EPATH]\nPS1 [%$PS1]\n(%D) [(%T)] (%t) (%*) (%w) (%H) (%h) [%%] [j%j] [!%!] [%m] [%u] [#/] [%~] [%?] %#"
#define DEFAULT_PS1 "%u@%m [%/]%# "

int ptr_modulo(shell_t *shell, char *input);
int ptr_handle_host(shell_t *shell, char *input);
int ptr_handle_user(shell_t *shell, char *input);
int ptr_handle_root(shell_t *shell, char *input);
int ptr_handle_return(shell_t *shell, char *input);
int ptr_handle_home(shell_t *shell, char *input);
int ptr_handle_pwd(shell_t *shell, char *input);
int ptr_handle_history(shell_t *shell, char *input);
int ptr_handle_jobs(shell_t *shell, char *input);
int ptr_handle_date(shell_t *shell, char *input);
int ptr_handle_time_24(shell_t *shell, char *input);
int ptr_handle_time_12(shell_t *shell, char *input);
int ptr_handle_sec(shell_t *shell, char *input);
int ptr_handle_week(shell_t *shell, char *input);
int ptr_handle_hour_24(shell_t *shell, char *input);
int ptr_handle_hour_12(shell_t *shell, char *input);
int ptr_handle_shell_var(shell_t *shell, char *input);
int ptr_handle_env_var(shell_t *shell, char *input);
int ptr_bold(shell_t *shell, char *input);
int ptr_underline(shell_t *shell, char *input);
int ptr_foreground(shell_t *shell, char *input);
int ptr_background(shell_t *shell, char *input);

static const struct {
	char token;
	int (*handler)(shell_t *shell, char *input);
} prompt[] = {
        {'%', &ptr_modulo},
        {'m', &ptr_handle_host},
        {'u', &ptr_handle_user},
        {'#', &ptr_handle_root},
        {'?', &ptr_handle_return},
        {'~', &ptr_handle_home},
        {'/', &ptr_handle_pwd},
        {'!', &ptr_handle_history},
        {'j', &ptr_handle_jobs},
        {'D', &ptr_handle_date},
        {'T', &ptr_handle_time_24},
        {'t', &ptr_handle_time_12},
        {'*', &ptr_handle_sec},
        {'w', &ptr_handle_week},
        {'H', &ptr_handle_hour_24},
        {'h', &ptr_handle_hour_12},
        {'$', &ptr_handle_shell_var},
        {'E', &ptr_handle_env_var},
        {'B', &ptr_bold},
        {'b', &ptr_underline},
        {'U', &ptr_foreground},
        {'F', &ptr_background},
	{0, NULL}
};

#endif
