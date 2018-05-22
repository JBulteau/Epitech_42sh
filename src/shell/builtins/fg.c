/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** fg = function to continue the jobs stoped
*/

#include <signal.h>
#include <stdio.h>
#include "minishell.h"
#include <unistd.h>
#include "my.h"

void set_node_running_false(void)
{
	jobs_t *node = find_node_job();

	node->running = false;
}

int kill_cont_childs(jobs_t *node)
{
	char *name = NULL;
	int i = 0;

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
	return (i);
}

int ptr_fg(comm_t *comm, shell_t *shell)
{
	int i;
	jobs_t *node;

	UNUSED(shell);
	UNUSED(comm);
	node = find_node_job();
	if (0 == get_nb_job() || node->pid_job[0] == 0) {
		printf("No jobs running\n");
		return (fflush(stdout), 1);
	}
	printf("\n[%d]", get_nb_job());
	i = kill_cont_childs(node);
	if (i == -1)
		return (-1);
	return (wait_for_it(node->pid_job[i - 1]));
}
