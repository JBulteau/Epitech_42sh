/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** functions for args parsing
*/

#include "my.h"
#include "parsing.h"

comm_t *check_comm(comm_t *comm)
{
	comm = check_redir(comm);
	if (comm == NULL)
		return (NULL);
	comm = check_pipe(comm);
	if (comm == NULL)
		return (NULL);
	comm = check_next(comm);
	if (comm == NULL)
		return (NULL);
	if ((comm && !comm->argv) || (comm && comm->argv && !comm->argv[0])) {
		free_comm(comm);
		return (NULL);
	}
	return (comm);
}

comm_t **slide_comm(comm_t **comm, int *i)
{
	for (int j = *i; comm[j + 1]; j++) {
		comm[j] = comm[j + 1];
		comm[j + 1] = NULL;
	}
	return (comm);
}

comm_t **parsing(shell_t *shell)
{
	node_t *node = init_node(shell->input, NONE);
	comm_t **comm = NULL;

	if (node == NULL)
		return (NULL);
	if (shell->input == NULL || shell->input[0] == '\0') {
		free_node(node);
		return (NULL);
	}
	node = parse_quote(node, shell);
	if (node == NULL)
		return (NULL);
	comm = init_comm_array(comm, node);
	comm = convert_node(comm, node, shell);
	for (int i = 0; comm && comm[i]; i++)
		if ((comm[i] = check_comm(comm[i])) == NULL)
			comm = slide_comm(comm, &i);
	free_node(node);
	return (comm);
}