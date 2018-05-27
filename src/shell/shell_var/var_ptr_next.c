/*
** EPITECH PROJECT, 2017
** var_ptr_next.c
** File description:
** Var pointers functon
*/

#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include "minishell.h"
#include "my.h"

int ptr_plusplus(char *name, int n, shell_t *shell)
{
	int id = find_var(shell->vars, name);

	UNUSED(n);
	if (id == ERROR_RETURN)
		shell->vars = set_var(shell->vars, name, "1");
	else
		shell->vars[id]->data.value++;
	return (0);
}

int ptr_minmin(char *name, int n, shell_t *shell)
{
	int id = find_var(shell->vars, name);

	UNUSED(n);
	if (id == ERROR_RETURN)
		shell->vars = set_var(shell->vars, name, "-1");
	else
		shell->vars[id]->data.value--;
	return (0);
}

int check_folder(char* path)
{
	DIR* directory = opendir(path);

	if (directory != NULL) {
		closedir(directory);
		return (1);
	} else
		return (0);
	return (-1);
}

char *search_folder(char *folder, char *name)
{
	char *fn = NULL;
	int rights[2] = {0, 0};

	if ((fn = concat(folder, concat("/", name, 0, 0), 0, 1)) == NULL)
		return (NULL);
	rights[0] = access(fn, F_OK);
	rights[1] = access(fn, X_OK);
	if (rights[0] == 0 && rights[1] == 0)
		return (fn);
	free(fn);
	return (NULL);
}