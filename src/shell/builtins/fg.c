/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** fg = function to continue the jobs stoped
*/

#include "builtins.h"
#include "minishell.h"
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>

int ptr_fg(comm_t *comm, shell_t *shell)
{
	int i = find_last_pid();

	if (pid_job[i] == -1 || pid_job[i] == -2) {
		puts("fg: no current job");
		return (1);
	}
	if (kill(pid_job[i], SIGCONT) == -1) {
		perror("kill");
		return (2);
	}
	printf("pid : %d -> continued\n", pid_job[i]);
	pid_job[i + 1] = -1;
	return (wait_for_it(pid_job[i]));
}
