/*
** EPITECH PROJECT, 2017
** alias_comm.c
** File description:
** Alias fnc that edits comm argv
*/

#include <string.h>
#include <stdio.h>
#include "minishell.h"
#include "my.h"

static int unalias_that_comm(alias_t *node, comm_t *comm)
{
	for (alias_t *curr = node; curr != NULL; curr = curr->nav[NEXT]) {
		if (!strcmp(comm->argv[0], curr->alias)) {
			//TODO EDIT TO HANLE SPACES ECT(eg char**)
			free(comm->argv[0]);
			comm->argv[0] = strdup(curr->name);
		}
	}
	return (EXIT_SUCCESS);
}

static int alias_that_comm(alias_t *node, comm_t *comm)
{
	for (alias_t *curr = node; curr != NULL; curr = curr->nav[NEXT]) {
		if (!strcmp(comm->argv[0], curr->name)) {
			//TODO EDIT TO HANLE SPACES ECT(eg char**)
			free(comm->argv[0]);
			comm->argv[0] = strdup(curr->alias);
		}
	}
	return (EXIT_SUCCESS);
}

int update_aliases(shell_t *shell, comm_t *comm, int remove, int skip_curr)
{
	int i = get_commidx(shell, comm);

	if (i == -1 || shell == NULL || shell->comm == NULL)
		return (ERROR_RETURN);
	if (shell->comm[i] == NULL)
		return (SUCCESS_RETURN);
	i += skip_curr;
	for (;shell->comm[i]; i++) {
		if (remove && (unalias_that_comm(shell->aliases, shell->comm[i]) == ERROR_RETURN)) {
			return (ERROR_RETURN);
		} else if (!remove && (alias_that_comm(shell->aliases, shell->comm[i]) == ERROR_RETURN)) {
			return (ERROR_RETURN);
		}
	}
	return (SUCCESS_RETURN);
}

int rm_alias(shell_t *shell, char *alias, comm_t *comm)
{
	alias_t *tmp = NULL;

	if (alias == NULL) {
		puts("Please specify an alias to remove");
		return (EXIT_FAILURE);
	}
	if (shell->aliases == NULL)
		return (EXIT_SUCCESS);
	for (alias_t *current = shell->aliases; current != NULL; current = current->nav[NEXT]) {
		if (!strcmp(current->name, alias) && (shell->aliases == current)) {
			shell->aliases = current->nav[NEXT];
			free_aliases(current, 0);
			current = shell->aliases;
		} else if (!strcmp(current->name, alias)) {
			update_aliases(shell, comm, 1, 1);
			free_aliases(current, 0);
			current = tmp;

		}
		tmp = current;
		if (current == NULL)
			break;
	}
	return (EXIT_SUCCESS);
}