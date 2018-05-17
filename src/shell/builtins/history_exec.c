/*
** EPITECH PROJECT, 2017
** history_exec.c
** File description:
** Function to exec an old command
*/

#include "minishell.h"

int run_last(history_t *hist)
{
        puts("Run last");
        return (0);
}

int run_n()
{
        puts("Run specific");
        return (0);
}

static int disp_help(void)
{
        printf("Usage\n\t!!\t\tre-run last command\n\t! [number]\tre-run [number] command\n");
        return (0);
}

int ptr_exec_his(comm_t *comm, shell_t *shell)
{
        if (!strcmp(comm->argv[0], "!!"))
                return(run_last(shell->history));
        if (comm->argv[0][1] == '\0' || (comm->argv[1]))
                return (disp_help());
        return (run_n());
}