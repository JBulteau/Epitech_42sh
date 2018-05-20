/*
** EPITECH PROJECT, 2017
** shell.c
** File description:
** Main shell functions
*/

#include <sys/types.h>
#include <signal.h>
#include <limits.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <unistd.h>
#include "minishell.h"
#include "prompt.h"
#include "my.h"

char **clone_arr(char **arr)
{
	int len = array_len((void *) arr);
	char **new_arr = NULL;

	if (len == -1) {
		new_arr = malloc(sizeof(char *) * 1);
		if (new_arr == NULL)
			return (NULL);
		new_arr[0] = NULL;
	} else {
		new_arr = malloc(sizeof(char *) * len);
		if (new_arr == NULL)
			return (NULL);
		for (int i = 0; arr[i]; i++)
			new_arr[i] = strdup(arr[i]);
		new_arr[len - 1] = NULL;
	}
	return (new_arr);
}

int setup_default_env(char ***env, shell_t *shell)
{
	char host[HOST_NAME_MAX];
	struct passwd *p = getpwuid(getuid());
	struct group *gr;

	#ifdef __x86_64__
		if (set_env_value(env, "MACHTYPE", "x86_64") == ERROR_RETURN)
	#else
		if (set_env_value(env, "MACHTYPE", "x86 or not x86_64") == ERROR_RETURN)
	#endif
			return (ERROR_RETURN);	
	if (set_env_value(env, "PWD", shell->pwd[0]) == ERROR_RETURN)
		return (ERROR_RETURN);
	if (p != NULL && set_env_value(env, "LOGNAME", p->pw_name) == ERROR_RETURN)
		return (ERROR_RETURN);
	if (p != NULL && set_env_value(env, "USER", p->pw_name) == ERROR_RETURN)
		return (ERROR_RETURN);
	if (!gethostname(host, HOST_NAME_MAX) && set_env_value(env, "HOST", host) == ERROR_RETURN)
		return (ERROR_RETURN);
	gr = getgrgid(p->pw_gid);
	if (gr != NULL && set_env_value(env, "GROUP", gr->gr_name) == ERROR_RETURN)
		return (ERROR_RETURN);
	if (set_infos(env) == ERROR_RETURN)
		return (ERROR_RETURN);
	return (SUCCESS_RETURN);
}

int set_shlvl(char ***env)
{
	int id = search_strtab((*env), "SHLVL=");
	int shlvl;
	char buff[32];

	if (id == -1) {
		if (set_env_value(env, "SHLVL", "1") == ERROR_RETURN)
			return (ERROR_RETURN);
		else
			return (SUCCESS_CODE);
	}
	shlvl = atoi((*env)[id] + 6);
	if (sprintf(buff, "%d", shlvl + 1) < 0)
		return (ERROR_RETURN);
	if (set_env_value(env, "SHLVL", buff) == ERROR_RETURN)
			return (ERROR_RETURN);
	return (SUCCESS_RETURN);
}

/*
** TODO: Add this to bonus folder
** if (load42(shell) == ERROR_RETURN)
** return (NULL);
*/
shell_t *init_shell(char **env)
{
	int create_default_env = (env == NULL || env[0] == NULL) ? 1 : 0;
	shell_t *shell = malloc(sizeof(shell_t));

	if (shell == NULL || (shell->env = clone_arr(env)) == NULL)
		return (NULL);
	shell->return_value = 0;
	shell->history_exec = 0;
	shell->history = NULL;
	shell->aliases = NULL;
	shell->input = NULL;
	if (getcwd(shell->pwd[0], PATH_MAX) == NULL)
		return (NULL);
	for (int i = 0; i < PATH_MAX; i++)
		shell->pwd[1][i] = '\0';
	if ((create_default_env && (setup_default_env(&(shell->env), shell) == ERROR_RETURN)) || (set_shlvl(&(shell->env)) == ERROR_CODE))
		return (NULL);
	if (isatty(STDIN_FILENO))
		if (set_env_value(&(shell->env), "PS1", DEFAULT_PS1) == ERROR_RETURN)
			return (NULL);
	if ((shell->vars = init_var_arr()) == NULL)
		return (NULL);
	return (shell);
}

void delete_shell(shell_t *shell)
{
	if (shell == NULL)
		return;
	free_array((void **) shell->env);
	free_history(shell->history);
	free(shell->input);
	free_aliases(shell->aliases, 1);
	for (int i = 0; shell->vars[i]; i++)
		free_var(shell->vars[i]);
	free(shell->vars);
	free(shell);
	for (int i = 0; pid_job[i] != -1 && pid_job[i] != -2; i++) {
		if (kill(pid_job[i], SIGKILL) == -1)
			perror("kill");
	}
	free(pid_job);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}