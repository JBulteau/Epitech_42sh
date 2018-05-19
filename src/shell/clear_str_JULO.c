/*
** EPITECH PROJECT, 2017
** clear_str_JULO.c
** File description:
** clear
*/

void init_clear_str(char *buffer, char **result)
{
	int nb = 0;
	int i = 0;

	for (; buffer[i] != '\0'; i++) {
		if ((buffer[i] == ' ' || buffer[i] == '\t'))
			for (; buffer[i + 1] == ' ' || \
buffer[i + 1] == '\t'; i++);
		nb++;
	}
	if (buffer[i - 1] == ' ' || buffer[i - 1] == '\t')
		nb--;
	if (buffer[0] == ' ' || buffer[0] == '\t')
		nb--;
	*result = malloc(sizeof(char) * (nb + 2));
	(*result)[nb + 1] = '\0';
}

void spaces_handle(int *a, char *result, int *i, char *buffer)
{
	int j = *i;

	for (; buffer[j] != '\0' && (buffer[j] == ' ' || \
buffer[j] == '\t'); j++);
	if (buffer[j] == '\0')
		j = 0;
	if (*a > 0 && j != 0) {
		result[*a] = ' ';
		(*a)++;
	}
	for (; (buffer[*i + 1] == ' ' || buffer[*i + 1] == '\t'); (*i)++);
}

char *clear_str(char *buffer)
{
	char *result = NULL;
	int a = 0;

	if (buffer == NULL)
		return (NULL);
	if (buffer[0] == '\0')
		return (buffer);
	init_clear_str(buffer, &result);
	for (int i = 0; buffer[i] != '\0'; i++) {
		if ((buffer[i] == ' ' || buffer[i] == '\t')) {
			spaces_handle(&a, result, &i, buffer);
			continue;
		}
	result[a++] = buffer[i];
	}
	result[a] = '\0';
	free(buffer);
	return (result);
}