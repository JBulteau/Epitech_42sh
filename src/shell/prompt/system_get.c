/*
** EPITECH PROJECT, 2017
** system_get.c
** File description:
** Functions handlers that get from libc fnc
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <limits.h>
#include "prompt.h"
#include "my.h"
#include "minishell.h"

int ptr_handle_host(shell_t *shell, char *input)
{
	char host[HOST_NAME_MAX];

	UNUSED(input);
	UNUSED(shell);
	gethostname(host, HOST_NAME_MAX);
	printf("%s", host);
	return (SUCCESS_RETURN);
}

int ptr_handle_user(shell_t *shell, char *input)
{
       	struct passwd *p = getpwuid(getuid());

	UNUSED(shell);
	UNUSED(input);
	printf("%s", p->pw_name);
	return (SUCCESS_RETURN);
}

int ptr_handle_root(shell_t *shell, char *input)
{
	struct passwd *p = getpwuid(getuid());

	UNUSED(shell);
	UNUSED(input);
	if (!strcmp(p->pw_name, "root"))
		putchar('#');
	putchar('>');
	return (SUCCESS_RETURN);
}

int ptr_handle_home(shell_t *shell, char *input)
{
	struct passwd *p = getpwuid(getuid());
	char *new_start = strstr(shell->pwd[0], p->pw_dir);

	UNUSED(input);
	if (new_start == NULL)
		printf("%s", shell->pwd[0]);
	else
		printf("~%s", new_start + strlen(p->pw_dir));
	return (SUCCESS_RETURN);
}