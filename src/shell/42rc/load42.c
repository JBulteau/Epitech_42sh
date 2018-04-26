/*
** EPITECH PROJECT, 2017
** load42.c
** File description:
** Functions that loads the .42rc file
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "my.h"
#include "minishell.h"

int ask_y_n(char *s, char *yes, char *no)
{
	int res;
	char *input;

	printf("%s [%s|%s]: ", s, yes, no);
	fflush(stdout);
	input = gnl(STDIN_FILENO);
	if (input == NULL || strcmp(input, yes))
		res = 0;
	else
		res = 1;
	free(input);
	return (res);
}

int load42(shell_t *shell)
{
	int create = 0;
	char *path42rc = concat(get_env_var(shell->env, "HOME="), concat("/", ".42rc", 0, 0), 1, 1);

	if (path42rc == NULL)
		return (ERROR_RETURN);
	if (access(path42rc, F_OK) == -1) {
		printf("File %s doesn't exists.\n", path42rc);
		if (ask_y_n("Do you want to create it ?", "y", "n")) {
			close(open(path42rc, O_CREAT | O_RDWR, 0644));
		} else {
			puts("Ok :'(");
		}
	} else {
		puts("We need you Julo !");
	}
	free(path42rc);
	return (0);
}