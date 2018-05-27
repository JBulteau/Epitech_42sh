/*
** EPITECH PROJECT, 2018
** history.c
** File description:
** Funtion that list all the command use since the begin of the shell
*/

#include <stdio.h>
#include <string.h>
#include "minishell.h"
#include "my.h"

history_t *create_new_case(char *s)
{
	history_t *new = malloc(sizeof(history_t));

	if (!new)
		return (NULL);
	new->data = strdup(s);
	new->next = NULL;
	return (new);
}

history_t *get_last(history_t *node)
{
	for (; node->next != NULL; node = node->next);
	return (node);
}

int save_history(shell_t *shell, char *input)
{
	history_t *nc = create_new_case(input);

	if (!nc)
		return (ERROR_RETURN);
	if (!shell->history) {
		shell->history = nc;
	} else {
		get_last(shell->history)->next = nc;
	}
	return (0);
}

int history_del(shell_t *shell, comm_t *comm)
{
	int i = 0;
	history_t *prev = NULL;

	if (comm->argv[2] == NULL)
		return (EXIT_FAILURE);
	for (history_t *curr = shell->history; curr != NULL; \
curr = curr->next) {
		if (++i == atoi(comm->argv[2])) {
			shell->history = (i == 1) ? curr->next : shell->history;
			prev->next = (i != 1) ? curr->next : prev->next;
			free(curr->data);
			free(curr);
			break;
		}
		prev = curr;
	}
	return (EXIT_SUCCESS);
}

int ptr_history(comm_t *comm, shell_t *shell)
{
	int i = 1;

	UNUSED(comm);
	if ((comm->argv) && (comm->argv[1]) && (!strcmp(comm->argv[1], "del") \
|| !strcmp(comm->argv[1], "delete") || !strcmp(comm->argv[1], "d"))) {
		return (history_del(shell, comm));
	}
	if ((comm->argv) && (comm->argv[1]) && ((!strcmp(comm->argv[1], "clear\
")) || !strcmp(comm->argv[1], "-c"))) {
		free_history(shell->history);
		shell->history = NULL;
		return (EXIT_SUCCESS);
	}
	for (history_t *curr = shell->history; curr != NULL; \
curr = curr->next) {
		printf("%i\t%s\n", i, (char *) curr->data);
		i++;
	}
	return (EXIT_SUCCESS);
}
