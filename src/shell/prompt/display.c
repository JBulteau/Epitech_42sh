/*
** EPITECH PROJECT, 2017
** display.c
** File description:
** Function tht display the prompt
*/

#include <stdio.h>
#include <string.h>
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
        int id = find_var(shell->vars, "PS1");
        char *prompt_var;
        int index;
        int len;
        int tmp;

        if (id == -1) {
                printf("> ");
                return (SUCCESS_CODE);
        }
        prompt_var = get_var_str(shell->vars[id]);
        len = strlen(prompt_var);
        for (int i = 0; i < len && prompt_var[i]; i++) {
                if (prompt_var[i] == '%') {
                        if ((index = find_hanlder(prompt_var[++i])) != ERROR_RETURN) {
                                if ((tmp = prompt[index].handler(shell, prompt_var + i + 1)) == ERROR_RETURN)
                                        break;
                                i += tmp;
                        } else
                                i++;
                } else {
                        putchar(prompt_var[i]);
                }
                fflush(stdout);
        }
        free(prompt_var);
        return (SUCCESS_RETURN);
}