/*
** EPITECH PROJECT, 2017
** system_get.c
** File description:
** Functions handlers that get from libc fnc
*/

#include <pwd.h>
#include <limits.h>
#include "prompt.h"
#include "my.h"
#include "minishell.h"

int ptr_handle_host(shell_t *shell)
{
        char host[HOST_NAME_MAX];

        gethostname(host, HOST_NAME_MAX);
        printf("%s", host);
        return (SUCCESS_RETURN);
}

int ptr_handle_user(shell_t *shell)
{
       	struct passwd *p = getpwuid(getuid());
        printf("%s", p->pw_name);
        return (SUCCESS_RETURN);
}

int ptr_handle_root(shell_t *shell)
{
	struct passwd *p = getpwuid(getuid());
        if (!strcmp(p->pw_name, "root"))
                putchar('#');
        putchar('>');
        return (SUCCESS_RETURN);
}

int ptr_handle_home(shell_t *shell)
{
        struct passwd *p = getpwuid(getuid());
        printf("%s <--> %s", p->pw_dir, shell->pwd[0]);
        return (SUCCESS_RETURN);
}