/*
** EPITECH PROJECT, 2017
** display.c
** File description:
** Function tht display the prompt
*/

#include <stdio.h>
#include "minishell.h"
#include "my.h"
#include "prompt.h"

int find_hanlder(char token)
{
        for (int i = 0; prompt[i].token; i++) {
                if (prompt[i].token == token)
                        return (i);
        }
        return (ERROR_RETURN);
}

int printf_prompt(shell_t *shell)
{
        char *prompt_var = get_env_var(shell->env, "PS1=");
        int index = 0;
        int displayed = 0;

        for (int i = 0; prompt_var[i]; i++) {
                if (prompt_var[i] == '%') {
                        if ((index = find_hanlder(prompt_var[++i])) != ERROR_RETURN && puts("GOTCHA"))
                                displayed += prompt[index].handler(shell);
                        else
                                i++;
                } else {
                        putchar(prompt_var[i]);
                }
        }
        free(prompt_var);
        return (displayed);
}