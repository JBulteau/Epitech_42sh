/*
** EPITECH PROJECT, 2018
** history.c
** File description:
** Funtion that list all the command use since the begin of the shell
*/

#include "builtins.h"
#include "minishell.h"

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
		return (-1);
	if (!shell->history) {
		shell->history = nc;
	} else {
		get_last(shell->history)->next = nc;
	}
	return (0);
}

void free_history(history_t *hist)
{
	if (hist == NULL)
		return;
	free(hist->data);
	free_history(hist->next);
	free(hist);
}

int ptr_history(comm_t *comm, shell_t *shell)
{
	for (history_t *curr = shell->history; curr != NULL; \
curr = curr->next) {
		puts((char *) curr->data);
	}
}
