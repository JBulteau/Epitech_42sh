/*
** EPITECH PROJECT, 2017
** tests_check_str.c
** File description:
** UT for check_str
*/

#include "my.h"
#include <criterion/criterion.h>

Test(check_str, is_num)
{
	cr_expect(is_num(NULL) == -1);
	cr_expect(is_num("aze") == -1);
	cr_expect(is_num("-aze") == -1);
	cr_expect(is_num("aze-") == -1);
	cr_expect(is_num("-aze-") == -1);
	cr_expect(is_num("42") == 0);
}

Test(check_str, is_alpha)
{
	cr_expect(is_alpha(NULL) == -1);
	cr_expect(is_alpha("aze") == 0);
	cr_expect(is_alpha("-aze") == -1);
	cr_expect(is_alpha("aze-") == -1);
	cr_expect(is_alpha("-aze-") == -1);
	cr_expect(is_alpha("AZE") == 0);
	cr_expect(is_alpha("-AZE") == -1);
	cr_expect(is_alpha("AZE-") == -1);
	cr_expect(is_alpha("-AZE-") == -1);
	cr_expect(is_alpha("42") == -1);
}

Test(check_str, is_alphanum)
{
	cr_expect(is_alphanum(NULL) == -1);
	cr_expect(is_alphanum("aze") == 0);
	cr_expect(is_alphanum("-aze") == -1);
	cr_expect(is_alphanum("aze-") == -1);
	cr_expect(is_alphanum("-aze-") == -1);
	cr_expect(is_alphanum("AZE") == 0);
	cr_expect(is_alphanum("-AZE") == -1);
	cr_expect(is_alphanum("AZE-") == -1);
	cr_expect(is_alphanum("-AZE-") == -1);
	cr_expect(is_alphanum("42") == 0);
	cr_expect(is_alphanum("A42") == 0);
	cr_expect(is_alphanum("42A") == 0);
	cr_expect(is_alphanum("2345REFERT543242A") == 0);
}

Test(check_str, index_of)
{
	cr_expect(index_of(NULL, 'a') == -1);
	cr_expect(index_of("abc", 'a') == 0);
	cr_expect(index_of("abc", 'A') == -1);
	cr_expect(index_of("reoifhrenzdezdezdfAregdnf", 'A') == 18);
}

Test(check_str, check_chars)
{
	cr_expect(check_chars(NULL, "abc") == -1);
	cr_expect(check_chars("abc", NULL) == -1);
	cr_expect(check_chars("Nope", "abcdefijklmnopqrstuvwxyz") == -1);
	cr_expect(check_chars("yes", "abcdefijklmnopqrstuvwxyz") == 0);
}