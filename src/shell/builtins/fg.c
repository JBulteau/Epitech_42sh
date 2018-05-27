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

void set_node_running_false(pid_t pid)
{
	jobs_t *node = list_jobs;

	while (node && is_in_list(node, pid) == 0)
		node = node->next;
	if (node)
		node->running = false;
}

int kill_cont_childs(jobs_t *node)
{
	char *name = NULL;
	int i = 0;

	for (; node->pid_job[i] != 0; i++) {
		if (kill(node->pid_job[i], SIGCONT) == -1)
			return (-1);
		name = get_proc_name(node->pid_job[i]);
		printf("\t%d - %s -> continued\n", node->pid_job[i], name);
		free(name);
	}
	node->running = true;
	fflush(stdout);
	return (i);
}

jobs_t *get_node_nb(int i)
{
	jobs_t *node = list_jobs;

	while (node != NULL && i > 0) {
		i--;
		node = node->next;
	}
	return (node);
}

int fg_arg(comm_t *comm)
{
	int nb;
	jobs_t *node;

	if (comm->argv[1][0] != '%')
		return (my_puterror("fg: No such job.\n"), 1);
	comm->argv[1][0] = '0';
	nb = atoi(comm->argv[1]);
	node = get_node_nb(nb);
	if (node == NULL)
		return (my_puterror("fg: No such job.\n"), 1);
	nb = kill_cont_childs(node);
	return (wait_for_it(node->pid_job[nb - 1]));
}

int ptr_fg(comm_t *comm, shell_t *shell)
{
	int i;
	jobs_t *node;

	UNUSED(shell);
	if (comm->argv[1])
		return (fg_arg(comm));
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
