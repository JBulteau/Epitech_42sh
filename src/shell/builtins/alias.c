/*
** EPITECH PROJECT, 2017
** alias.c
** File description:
** Builtins alias
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include <string.h>

alias_t *create_alias(char *name, char*alias, alias_t *prev)
{
        alias_t *new = malloc(sizeof(alias_t) * 1);

        if (new == NULL)
                return (NULL);
        new->alias = alias;
        new->name = name;
        new->nav[PREV] = prev;
        new->nav[NEXT] = NULL;
        return (new);
}

int disp_aliases(alias_t *node)
{
        if (node == NULL) {
                puts("No alias set");
                return (0);
        }
        for (alias_t *current = node; current != NULL; current = current->nav[NEXT])
                printf("%s=%s\n", current->name, current->alias);
        return (0);
}

int disp_help(void)
{
        puts("Usage: alias [rm] [name[=alias]]");
        return (0);
}

int add_alias(char **args, shell_t *shell)
{
        alias_t *last = NULL;

        if (shell->aliases == NULL) {
                puts("INIT");
                shell->aliases = create_alias("name", "alias", NULL);
                return (0);
        }
        puts("ADDING");
        for (; last->nav[NEXT] != NULL; last = last->nav[NEXT]);
        last->nav[NEXT] = create_alias("name", "alias", last);
        return (0);
}

int rm_alias(shell_t *shell)
{
        return (0);
}

int ptr_alias(comm_t *comm, shell_t *shell)
{
        if (comm->argv[1] == NULL)
                return (disp_aliases(shell->aliases));
        if (!strcmp(comm->argv[1], "--help") || !strcmp(comm->argv[1], "-h"))
                return (disp_help());
        if (!strcmp(comm->argv[1], "rm") || !strcmp(comm->argv[1], "delete"))
                return (rm_alias(shell));
        return (add_alias(comm->argv + 1, &(shell->aliases)));
}