/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** init the signals and init for jobs
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "my.h"

pid_t *pid_job;

char* get_proc_name(pid_t pid)
{
	char* name = malloc(sizeof(char) * 1024);
	size_t size;
	int fd;

	if (name == NULL)
		return (NULL);
	sprintf(name, "/proc/%d/cmdline", pid);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	size = read(fd, name, 1024);
	name[size - 1] = '\0';
	close(fd);
	return (name);
}

void catch_ctrl_z(int sig)
{
	int i = find_last_pid();
	char *name;

	UNUSED(sig);
	printf("\033[2D  \033[2D");
	if (pid_job[i] == -1 || pid_job[i] == -2 || \
(pid_job[i + 1] && pid_job[i + 1] == -2))
		return;
	if (kill(pid_job[i], SIGSTOP) == -1) {
		perror("kill");
		return;
	}
	if (raise(SIGCONT) == -1) {
		perror("raise");
		return;
	}
	name = get_proc_name(pid_job[i]);
	printf("\n[%d] : %d - %s -> suspended\n", i + 1, pid_job[i], name);
	pid_job[i + 1] = -2;
	free(name);
}

void catch_ctrl_c(int sig)
{
	int i = find_last_pid();

	UNUSED(sig);
	if (pid_job[i] == -1 || pid_job[i] == -2 || \
(pid_job[i + 1] && pid_job[i + 1] == -2)) {
		printf("\033[2D  \n");
		//DESO MIKE JE CHERCHE PLUS TARD SI Y'A MOY DEFAIRE AUTREMENT
		//disp_prompt();
	}
}

int init_signal(void)
{
	struct sigaction act_z;
	struct sigaction act_c;

	pid_job = malloc(sizeof(int) * 2);
	if (memset(&act_z, '\0', sizeof(act_z) + 1) == NULL || \
memset(&act_c, '\0', sizeof(act_z) + 1) == NULL || pid_job == NULL)
		return (-1);
	pid_job[0] = -1;
	act_z.sa_sigaction = (void *)catch_ctrl_z;
	act_c.sa_sigaction = (void *)catch_ctrl_c;
	sigaction(SIGTSTP, &act_z, NULL);
	sigaction(SIGINT, &act_c, NULL);
	return (0);
}

int wait_for_it(pid_t pid)
{
	pid_t father = getpid();
	pid_t last_pid;
	int status = 0;

	do {
		last_pid = wait(&status);
		if (!WIFSIGNALED(status))
			continue;
		if (WTERMSIG(status) == 8)
			fprintf(stderr, "Floating exception");
		else
			fprintf(stderr, strsignal(WTERMSIG(status)));
		if (WCOREDUMP(status))
			fprintf(stderr, " (core dumped)");
		fprintf(stderr, "\n");
	} while (last_pid != pid && last_pid != father && last_pid != -1);
	if (last_pid != father && last_pid != -1)
		remove_last_pid();
	return ((WTERMSIG(status)) ? status : WEXITSTATUS(status));
}