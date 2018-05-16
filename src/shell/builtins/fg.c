/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** fg = function to continue the jobs stoped
*/

#include <signal.h>
#include "minishell.h"
#include "stdio.h"

int ptr_fg(comm_t *comm, shell_t *shell)
{
	int i = find_last_pid();
	char *name;

	if (pid_job[i] == -1 || pid_job[i] == -2) {
		puts("fg: no current job");
		return (1);
	}
	if (kill(pid_job[i], SIGCONT) == -1) {
		perror("kill");
		return (2);
	}
	name = get_proc_name(pid_job[i]);
	printf("[%d] %d - %s -> continued\n", i + 1, pid_job[i], name);
	pid_job[i + 1] = -1;
	free(name);
	return (wait_for_it(pid_job[i]));
}
