/*
** EPITECH PROJECT, 2017
** infos.c
** File description:
** Infos that shoudl be set at compil
*/

#include "minishell.h"
#include "my.h"

int set_infos(char ***env)
{
	#ifdef __OSTYPE__
	if (set_env_value(env, "OSTYPE", __OSTYPE__) == ERROR_RETURN)
		return (ERROR_RETURN);
	#endif
	#ifdef __MACHTYPE__
	if (set_env_value(env, "MARCHTYPE", __MACHTYPE__) == ERROR_RETURN)
		return (ERROR_RETURN);
	#endif
	#ifdef __VENDOR__
	if (set_env_value(env, "VENDOR", __VENDOR__) == ERROR_RETURN)
		return (ERROR_RETURN);
	#endif
	#ifdef __HOSTTYPE__
	if (set_env_value(env, "HOSTTYPE", __HOSTTYPE__) == ERROR_RETURN)
		return (ERROR_RETURN);
	#endif
	UNUSED(env);
	return (SUCCESS_RETURN);
}