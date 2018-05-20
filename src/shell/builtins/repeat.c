/*
** EPITECH PROJECT, 2017
** repeat.c
** File description:
** repeat fnc
*/

#include <stdio.h>
#include <string.h>
#include "minishell.h"
#include "my.h"

static int disp_help(void)
{
        puts("Usage:\n\trepeat <N> <command>");
        return (SUCCESS_CODE);
}

int ptr_repeat(comm_t *comm, shell_t *shell)
{
        int repeat = 0;
        char **save = comm->argv;
        int comm_id = get_commidx(shell, comm);

        if ((comm->argv) && (((comm->argv[1]) && (!strcmp(comm->argv[1], "--help") || !strcmp(comm->argv[1], "-h"))) || (comm->argv[2] == NULL)))
		return (disp_help());
        repeat = atoi(comm->argv[1]);
        if (repeat == 0) {
                puts("Please enter a positive integer");
                return (shell->return_value = 0);
        }
        if (comm_id == -1)
                repeat = 1;
        for (int i = 0; i < repeat; i++) {
                comm->argv += 2;
                shell->return_value = run_pipeline(shell, comm);
                comm->argv = save;
        }
        return (SUCCESS_RETURN);
}