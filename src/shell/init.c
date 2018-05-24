/*
** EPITECH PROJECT, 2017
** init.c
** File description:
** Shell init functions
*/

#include <limits.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <unistd.h>
#include "prompt.h"
#include "minishell.h"
#include "my.h"

int set_basic_env(shell_t *shell, char ***env)
{
	char host[HOST_NAME_MAX];
	struct passwd *p = getpwuid(getuid());
	struct group *gr;

	if (set_env_value(env, "PWD", shell->pwd[0]) == ERROR_RETURN)
		return (ERROR_RETURN);
	if (p != NULL && set_env_value(env, "LOGNAME", p->pw_name) == \
ERROR_RETURN)
		return (ERROR_RETURN);
	if (p != NULL && set_env_value(env, "USER", p->pw_name) == \
ERROR_RETURN)
		return (ERROR_RETURN);
	if (!gethostname(host, HOST_NAME_MAX) && set_env_value(env, "HOST", \
host) == ERROR_RETURN)
		return (ERROR_RETURN);
	gr = getgrgid(p->pw_gid);
	if (gr != NULL && set_env_value(env, "GROUP", gr->gr_name) == \
ERROR_RETURN)
		return (ERROR_RETURN);
	return (SUCCESS_RETURN);
}

int setup_default_env(char ***env, shell_t *shell)
{
	#ifdef __x86_64__
	if (set_env_value(env, "MACHTYPE", "x86_64") == ERROR_RETURN)
	#else
	if (set_env_value(env, "MACHTYPE", "x86 or not x86_64") == \
ERROR_RETURN)
	#endif
		return (ERROR_RETURN);
	if (set_basic_env(shell, env) == ERROR_RETURN)
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

int init_vars(shell_t *shell)
{
	for (shell->vars = init_var_arr(); !shell->vars;)
		return (ERROR_RETURN);
	if (isatty(STDIN_FILENO))
		for (shell->vars = set_var(shell->vars, "PS1", DEFAULT_PS1); \
!shell->vars;)
			return (ERROR_RETURN);
	for (shell->vars = set_var(shell->vars, "path", DEFAULT_PATH); \
!shell->vars;)
		return (ERROR_RETURN);
	return (SUCCESS_RETURN);
}