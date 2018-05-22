/*
** EPITECH PROJECT, 2017
** handler_date.c
** File description:
** Handler for dates
*/

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "prompt.h"
#include "minishell.h"
#include "my.h"

char *get_day(int day)
{
        switch (day) {
                case 0: return (strdup("Mon"));
                case 1: return (strdup("Tue"));
                case 2: return (strdup("Wed"));
                case 3: return (strdup("Thu"));
                case 4: return (strdup("Fri"));
                case 5: return (strdup("Sat"));
                case 6: return (strdup("Sun"));
        }
        return (NULL);
}

int ptr_handle_date(shell_t *shell, char *input)
{
        time_t t = time(NULL);
        struct tm tm;

        UNUSED(input);
        UNUSED(shell);
        if (t != -1)
                tm = *localtime(&t);
        else
                return (ERROR_RETURN);
        printf("%02d-%02d-%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
        return (SUCCESS_RETURN);
}

int ptr_handle_week(shell_t *shell, char *input)
{
        time_t t = time(NULL);
        struct tm tm;
        char *day = NULL;

        UNUSED(input);
        UNUSED(shell);
        if (t != -1)
                tm = *localtime(&t);
        else
                return (ERROR_RETURN);
        day = get_day(tm.tm_wday);
        if (day == NULL)
                return (ERROR_RETURN);
        printf("%s %02d", day, tm.tm_mday);
        free(day);
        return (SUCCESS_RETURN);
}