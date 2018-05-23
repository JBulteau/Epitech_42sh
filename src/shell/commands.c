/*
** EPITECH PROJECT, 2017
** commands.c
** File description:
** Functions that manages commands
*/

#include "tokens.h"
#include "minishell.h"
#include "my.h"

void free_comm(comm_t *comm)
{
	if (comm->pipe[OUT]) {
		free_comm(comm->pipe[OUT]->output);
		free(comm->pipe[OUT]);
	}
	free_array((void **) comm->argv);
	free_red(comm->red[S_RIGHT]);
	free_red(comm->red[S_LEFT]);
	free_red(comm->red[D_LEFT]);
	free_red(comm->red[D_RIGHT]);
	if (comm->next)
		free_comm(comm->next);
	free(comm);
	return;
}

comm_t *init_comm(void)
{
	comm_t *comm = malloc(sizeof(comm_t) * 1);

	if (comm == NULL)
		return (NULL);
	for (int j = 0; j <= 3; j++)
		comm->red[j] = NULL;
	if ((comm->argv = malloc(sizeof(char **) * 1)) == NULL)
		return (NULL);
	comm->argv[0] = NULL;
	comm->pipe[OUT] = NULL;
	comm->pipe[IN] = NULL;
	comm->fg = false;
	comm->separator = NOTHING;
	comm->next = NULL;
	return (comm);
}

void free_comms(comm_t **comm)
{
	for (int i = 0; comm[i]; i++) {
		free_comm(comm[i]);
	}
	free(comm);
}

int get_commidx(shell_t *shell, comm_t *comm)
{
	int i = 0;

	if (shell == NULL || comm == NULL)
		return (ERROR_RETURN);
	for (; shell->comm[i]; i++)
		if (shell->comm[i] == comm)
			return (i);
	return (ERROR_RETURN);
}

int run_that(shell_t *shell)
{
	int return_code = 0;

	if ((shell->comm = parsing(shell->input)) == NULL)
		return (ERROR_CODE);
	if (update_aliases(shell, shell->comm[0], 0, 0) == ERROR_RETURN)
		return (ERROR_CODE);

	/*DEBUG
	shell->comm[0]->next = shell->comm[1];
	shell->comm[1]->next = shell->comm[2];
	shell->comm[2]->next = shell->comm[3];
	shell->comm[3]->next = NULL;
	shell->comm[1] = NULL;
	shell->comm[2] = NULL;
	shell->comm[3] = NULL;
	/*END OF DEBUG*/
	return_code = exec_loop(shell);
	if (shell->comm != NULL)
		free_comms(shell->comm);
	return (return_code);
}
