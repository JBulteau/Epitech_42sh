/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** fg = function to continue the jobs stoped
*/

#include <signal.h>
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

void set_node_running_false(void)
{
	jobs_t *node = find_node_job();

	node->running = false;
}

int ptr_fg(comm_t *comm, shell_t *shell)
{
	int i = 0;
	jobs_t *node;
	char *name;

	remove_node();
	node = find_node_job();
	if (0 == get_nb_job() || node->pid_job[0] == 0) {
		printf("No jobs running\n");
		return (fflush(stdout), 1);
	}
	printf("\n[%d]", get_nb_job());
	for (; node->pid_job[i] != 0; i++) {
		if (kill(node->pid_job[i], SIGCONT) == -1) {
			perror("kill");
			return (-1);
		}
		name = get_proc_name(node->pid_job[i]);
		printf("\t%d - %s -> continued\n", node->pid_job[i], name);
		free(name);
	}
	node->running = true;
	fflush(stdout);
	return (wait_for_it(node->pid_job[i - 1]));
}
