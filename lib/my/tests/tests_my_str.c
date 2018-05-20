/*
** EPITECH PROJECT, 2017
** tests_check_str.c
** File description:
** UT for str
*/

#include "my.h"
#include <criterion/criterion.h>

Test (str, strlen)
{
        cr_expect(my_strlen(NULL) == -1);
        cr_expect(my_strlen("ABC") == 3);
}

Test (str, strncpy)
{
        char *buff = strdup("AAAAAAAAAAAAAAAAAAA");

        cr_expect(my_strcpy(NULL, "ABC", 0) == NULL);
        cr_expect(my_strcpy("ABC", NULL, 0) == NULL);
        my_strcpy(buff, "IJK", 0);
        cr_expect(strcmp(buff, "IJKAAAAAAAAAAAAAAAA") == 0);
        my_strcpy(buff, "VACHEMENT LONG", 4);
        cr_expect(strcmp(buff, "VACHAAAAAAAAAAAAAAA") == 0);
        free(buff);
}

Test (str, strncmp)
{
        cr_expect(my_strcmp(NULL, "ABC", 0) == 1);
        cr_expect(my_strcmp("abc", NULL, 0) == 1);
        cr_expect(my_strcmp("ABC", "ABC", 0) == 0);
        cr_expect(my_strcmp("ABC", "ABJ", 2) == 0);
        cr_expect(my_strcmp("ABC", "ABCD", 0) == 1);
        cr_expect(my_strcmp("ABC", "ABD", 0) == 1);
        cr_expect(my_strcmp("IBC", "IgenBD", 5) == 1);
}

Test (str, strndup)
{
        char *buff = my_strndup("ABC", 0);

        cr_expect(my_strcmp(buff, "ABC", 0) == 0);
        free(buff);
        buff = strndup("ABCDEFIJK", 3);
        cr_expect(my_strcmp(buff, "ABC", 0) == 0);
        free(buff);
}


Test (str, revstr)
{
        char *original = "chauve";
        char *new = NULL;

        new = my_revstr(new);
        cr_expect(new == NULL);        
        new = my_revstr(original);
        cr_expect(my_strcmp(new, "evuahc", 0) == 0);
        free(new);
}