/*
** EPITECH PROJECT, 2017
** handler_date.c
** File description:
** Handler for dates
*/

#include <time.h>
#include "prompt.h"
#include "minishell.h"
#include "my.h"

/*int get_day(int day, char *des)
{
        switch (day) {
                case 0: return (strcpy(des, "Mon"));
                case 1: return (strcpy(des, "Tue"));
                case 2: return (strcpy(des, "Wed"));
                case 3: return (strcpy(des, "Thu"));
                case 4: return (strcpy(des, "Fri"));
                case 5: return (strcpy(des, "Sat"));
                case 6: return (strcpy(des, "Sun"));
        }
}*/

int ptr_handle_date(shell_t *shell)
{
        time_t t = time(NULL);
        struct tm tm;

        if (t != -1)
                tm = *localtime(&t);
        else
                return (ERROR_RETURN);
        printf("%d-%d-%d", tm.tm_mday, tm.tm_mon, tm.tm_year + 1900);
        return (SUCCESS_CODE);}

int ptr_handle_week(shell_t *shell)
{
        time_t t = time(NULL);
        struct tm tm;

        if (t != -1)
                tm = *localtime(&t);
        else
                return (ERROR_RETURN);
        printf("%d %d", tm.tm_wday, tm.tm_mday);
        return (SUCCESS_CODE);
}