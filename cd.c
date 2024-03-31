#include <unistd.h>
#include "str.h"

/**
 * _cd_logic - uses chdir to change working directory
 * @dest: destination of new directory
 */
void _cd_logic(char *dest)
{
	if (chdir(dest) == -1)
		perror("bash: cd");
}

/**
 * _strlen - get lenght of string
 * @s: input string
 * Return: length of string
 */
int _strlen(const char *s)
{
	int count = 0;

	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}

/**
 * _strncpy - copies n chars from src to dest
 * @destination: destination string
 * @source: source string
 * @num: number of chars to be copied
 * Return: ptr to destination string
 */
char *_strncpy(char *destination, const char *source, size_t num)
{
	char *ptr = destination;

	if (destination == NULL)
	{
		return (NULL);
	}

	while (*source && num--)
	{
		*destination = *source;
		destination++;
		source++;
	}

	*destination = '\0';
	return (ptr);
}

/**
 * _strcat - concat source to dest string
 * @destination: dest string
 * @source: src string
 * Return: ptr to dest string
 */
char *_strcat(char *destination, const char *source)
{
	char *ptr = destination + _strlen(destination);

	while (*source != '\0')
		*ptr++ = *source++;

	*ptr = '\0';

	return (destination);
}


/**
 * handle_token - handles to tokenization of getline
 * @line: value getline
 * @argv: array that the arguments of command will get inserted
 * @i: ptr to array cells
 */
void handle_token(char *line, char **argv, int *i)
{
	char *token;

	if (!line)
		return;
	token = strtok(line, " ");
	*i = 0;
	while (token)
	{
		argv[*i] = token;
		token = strtok(NULL, " ");
		(*i)++;
	}
	argv[*i] = NULL;
}

