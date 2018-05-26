/*
** EPITECH PROJECT, 2017
** magic_quotes.c
** File description:
** MAgic quotes functions
*/

#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"
#include "my.h"


static int redir_start(int fd[2], char *template)
{
	fd[0] = mkstemp(template);
	fd[1] = dup(STDOUT_FILENO);
	if (fd[0] == -1 || fd[1] == -1 || dup2(fd[0], STDOUT_FILENO) == -1)
		return (ERROR_RETURN);
	return (SUCCESS_RETURN);
}

static int redir_end(int fd[2], char *template)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (ERROR_RETURN);
	close(fd[1]);
	if (unlink(template) == ERROR_RETURN)
		return (ERROR_RETURN);
	return (SUCCESS_RETURN);
}

char *get_str(int fd)
{
	char *buffer;
	int size;

	size = lseek(fd, (size_t)0, SEEK_END);
	if (size == ERROR_RETURN)
		return (NULL);
	if (lseek(fd, (size_t)0, SEEK_SET) == ERROR_RETURN)
		return (NULL);
	buffer = malloc(sizeof(char) * (size + 1));
	buffer[size] = '\0';
	if (buffer == NULL)
		return (NULL);
	if (read(fd, buffer, size) < 0)
		return (NULL);
	return (buffer);
}

char *get_magic(shell_t *shell, char *comm)
{
	char template[] = "/tmp/42shXXXXXX";
	char *magic = NULL;
	shell_t *dup = dup_shell(shell);
	int fd[2];

	dup->input = comm;
	if (redir_start(fd, template) == ERROR_RETURN)
		return (NULL);
	if (run_that(dup) == ERROR_RETURN)
	free_aliases(dup->aliases, 1);
	free_history(dup->history);
	for (int i = 0; dup->vars[i]; i++)
		free_var(dup->vars[i]);
	free(dup->vars);
	free_array((void **)dup->env);
	free(comm);
	free(dup);
	magic = get_str(fd[0]);
	if (redir_end(fd, template) == ERROR_RETURN)
		return (NULL);
	return (magic);
}

history_t *dup_history(history_t *node)
{
	history_t *new = NULL;

	if (node == NULL)
		return (NULL);
	new = malloc(sizeof(history_t) * 1);
	if (new == NULL)
		return (NULL);
	new->data = strdup(node->data);
	new->next = dup_history(node->next);
	return (new);
}