/*
** EPITECH PROJECT, 2017
** handler_vars.c
** File description:
** Handler for vars
*/

#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "prompt.h"
#include "minishell.h"
#include "my.h"

int ptr_handle_env_var(shell_t *shell, char *input)
{
        int index = 0;
        char save;
        int len;
        char *var_value = NULL;

        for (index = 0; isalnum(input[index]); index++);
        save = input[index];
        input[index] = '\0';
        var_value = get_env_var(shell->env, input);
        if (var_value == NULL)
                return (ERROR_RETURN);
        len = strlen(input);
        write(STDOUT_FILENO, var_value + 1, strlen(var_value + 1));
        input[index] = save;
        free(var_value);
        return (SUCCESS_RETURN + len);
}

int ptr_handle_shell_var(shell_t *shell, char *input)
{
        int index;
        char save;
        int len;
        int id;
        char *str_var = NULL;

        for (index = 0; isalnum(input[index]); index++);
        save = input[index];
        input[index] = '\0';
        len = strlen(input);
        id = find_var(shell->vars, input);
        if (id == ERROR_RETURN)
                return (ERROR_RETURN);
        str_var = get_var_str(shell->vars[id]);
        if (str_var == NULL)
                return (ERROR_RETURN);
        write(1, str_var, strlen(str_var));
        input[index] = save;
        free(str_var);
        return (SUCCESS_RETURN + len);
}