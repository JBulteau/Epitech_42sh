/*
** EPITECH PROJECT, 2017
** search.c
** File description:
** Path + search for exec fnc
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "my.h"
#include "minishell.h"

void disp_rights(char *name, int exists, int exec)
{
	if (exists == -1) {
		fprintf(stderr, "%s: Command not found.\n", name);
	} else if (exec == -1) {
		fprintf(stderr, "%s: Permission denied.\n", name);
	}
}

int search_local(char *name)
{
	int rights[2] = {0, 0};

	rights[0] = access(name, F_OK);
	if (rights[0] != -1)
		rights[1] = access(name, X_OK);
	if (check_is_dir(name) == 1)
		rights[1] = -1;
	disp_rights(name, rights[0], rights[1]);
	return ((rights[0] == 0 && rights[1] == 0) ? 0 : 1);
}

char *search_path(char **path, char *name)
{
	char *fn = NULL;
	int rights[2] = {0, 0};

	for (int i = 0; path[i] != NULL; i++) {
		if ((fn = concat(path[i], concat("/", name, 0, 0), 0, 1)) \
== NULL)
			return (NULL);
		rights[0] = access(fn, F_OK);
		rights[1] = access(fn, X_OK);
		if (rights[0] == 0 && rights[1] == 0)
			return (fn);
		if (rights[0] == 0 && rights[1] == -1) {
			disp_rights(fn, rights[0], rights[1]);
			free(fn);
			return (NULL);
		}
		free(fn);
	}
	disp_rights(name, -1, 0);
	return (NULL);
}

char *get_env_var(char **env, char *var)
{
	char *res = NULL;
	int len = strlen(var);

	if (env == NULL || var == NULL)
		return (NULL);
	for (int key = 0; env[key] != NULL; key++)
		if (strncmp(env[key], var, len) == 0)
			res = strdup(env[key] + len);
	if (res == NULL)
		return (NULL);
	return (res);
}

char **get_path(char **env, var_t **vars)
{
	char **path = NULL;

	if (env == NULL)
		return (NULL);
	for (int key = 0; env[key] != NULL; key++)
		if (strncmp(env[key], "PATH=", 5) == 0)
			path = strwordarr(env[key] + 5, ":");
	for (int key = 0; !path && vars && vars[key] != NULL; key++)
		if (!strcmp(vars[key]->name, "path"))
			path = strwordarr(vars[key]->data.content, ":");
	if (path == NULL)
		return (NULL);
	return (path);
}