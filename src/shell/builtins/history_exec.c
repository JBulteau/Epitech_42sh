/*
** EPITECH PROJECT, 2017
** history_exec.c
** File description:
** Function to exec an old command
*/

#include <stdio.h>
#include <string.h>
#include "minishell.h"
#include "builtins.h"
#include "my.h"

int run_last(shell_t *shell)
{
	int return_c = 0;
	comm_t **save = shell->comm;
	history_t *hist = shell->history;

	for (; hist->next != NULL && hist->next->next != NULL; hist = \
hist->next);
	free(shell->input);
	shell->input = strdup(hist->data);
	if (shell->input == NULL)
		return (ERROR_RETURN);
	shell->history_exec = 1;
	return_c = run_that(shell);
	shell->history_exec = 0;
	shell->comm = save;
	return (return_c);
}

int event_not_found(shell_t *shell, int n)
{
	UNUSED(shell);
	fprintf(stderr, "%i: Event not found.\n", n);
	return (EXIT_FAILURE);
}

int run_n(shell_t *shell, int n)
{
	int return_c = 0;
	comm_t **save;
	history_t *hist = shell->history;
	int i;

	if (n < 0)
		return (ERROR_RETURN);
	for (i = 1; i < n && hist->next != NULL; i++)
		hist = hist->next;
	if (i != n)
		return (event_not_found(shell, n));
	save = shell->comm;
	free(shell->input);
	shell->input = strdup(hist->data);
	if (shell->input == NULL)
		return (ERROR_RETURN);
	shell->history_exec = 1;
	return_c = run_that(shell);
	shell->history_exec = 0;
	shell->comm = save;
	return (return_c);
}

static int disp_help(void)
{
	printf("Usage\n\t!!\t\tre-run last command\n\t! [number]\tre-run \
[number] command\n");
	return (0);
}

int ptr_exec_his(comm_t *comm, shell_t *shell)
{
	int return_val = 0;

	if (!strcmp(comm->argv[0], "!!"))
		return (run_last(shell));
	if (comm->argv[0][1] == '?')
		return (ptr_history(comm, shell));
	if (shell->history_exec) {
		puts("History recursion not allowed");
		shell->return_value = 1;
		return (1);
	}
	if (!strcmp(comm->argv[0], "!!"))
		return (run_last(shell));
	if (comm->argv[0][1] == '\0' || (comm->argv[1]))
		return (disp_help());
	return_val = run_n(shell, atoi(comm->argv[0] + 1));
	if (return_val == ERROR_RETURN)
		return (return_val);
	return (return_val);
}