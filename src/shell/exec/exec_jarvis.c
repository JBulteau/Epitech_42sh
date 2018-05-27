/*
** EPITECH PROJECT, 2017
** exec_jarvis.c
** File description:
** Functions to exec javis
*/

#include "minishell.h"
#include "my.h"

int call_jarvis_rerun(shell_t *shell)
{
	int changed = exec_on_comm_arr(shell);
	int return_v = 0;

	if (changed) {
		printf("Jarvis changed %i comm(s)\n", changed / 2);
		return_v = exec_loop(shell, shell->comm);
	}
	return (return_v);
}

int exec_on_comm(comm_t *curr, shell_t *shell)
{
	int edited[3] = {0, 0, 0};

	if (curr->pipe[OUT] && curr->pipe[OUT]->output) {
		edited[0] = exec_on_comm(curr->pipe[OUT]->output, shell);
		if (edited[0] == ERROR_RETURN)
			return (ERROR_RETURN);
	} if (curr->next) {
		edited[1] = exec_on_comm(curr->next, shell);
		if (edited[1] == ERROR_RETURN)
			return (ERROR_RETURN);
	}
	edited[2] = jarvis_corrector(curr, &(shell->env));
	if (edited[2] == ERROR_RETURN)
		return (ERROR_RETURN);
	return (edited[0] + edited[1] + edited[2]);
}

int exec_on_comm_arr(shell_t *shell)
{
	int edited = 0;
	int last_return;

	for (int i = 0; shell->comm[i]; i++) {
		last_return = exec_on_comm(shell->comm[i], shell);
		if (last_return == ERROR_RETURN)
			return (ERROR_RETURN);
		else
			edited += last_return;
	}
	return (edited);
}