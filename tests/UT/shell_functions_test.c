/*
** EPITECH PROJECT, 2017
** shell.c
** File description:
** Basic UT for shell
*/

#include "minishell.h"
#include <criterion/criterion.h>

Test(basic_shell, init_null_env)
{
	shell_t *shell = init_shell(NULL);

	cr_expect(shell->input == NULL);
	cr_expect(shell->env != NULL);
	cr_expect(shell->comm == NULL);
	cr_expect(shell->return_value == 0);
}

Test(basic_shell, init_no_null_env)
{
	char *env[] = {
		"ABC",
		"ENV",
		NULL
	};
	shell_t *shell = init_shell(env);

	cr_expect(shell->input == NULL);
	cr_expect(shell->env != NULL);
	cr_expect(!strcmp(shell->env[0], "ABC"));
	cr_expect(!strcmp(shell->env[1], "ENV"));
	cr_expect(shell->comm == NULL);
	cr_expect(shell->return_value == 0);
}