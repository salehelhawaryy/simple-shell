#include "str.h"

/**
 * _strncmp - compares first n characters of two strings
 * @s1: string one
 * @s2: string two
 * @n: number of chars
 * Return: 0 for equal
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && (*s1 == *s2))
	{
		++s1;
		++s2;
		--n;
	}
	if (n == 0)
	{
		return (0);
	}
	else
	{
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
	}
}


/**
 * _printenv - prints the environment
 */
void _printenv(void)
{
	char output[4096];
	char *command = "sh -c env";
	size_t bytesRead;
	FILE *pipe = popen(command, "r");

	if (pipe == NULL)
		fprintf(stderr, "Failed to execute command: %s\n", command);
	bytesRead = fread(output, 1, sizeof(output) - 1, pipe);
	output[bytesRead] = '\0';
	pclose(pipe);
	printf("%s", output);
}


/**
 * _strdup - duplicates input string and returns it
 * @src: source string to be duplicated
 * Return: ptr to new string
 */
char *_strdup(char *src)
{
	char *str;
	char *p;
	int len = 0;

	while (src[len])
		len++;
	str = malloc(len + 1);
	p = str;
	while (*src)
		*p++ = *src++;
	*p = '\0';
	return (str);
}

/**
 * _strchr - returns point to location of c in s
 * @s: given string
 * @c: given char
 * Return: ptr to char's location
 */
char *_strchr(char *s, char c)
{
	while (*s != c && *s != '\0')
	{
		s++;
	}
	if (*s == c)
	{
		return (s);
	}
	else
	{
		return (NULL);
	}
}

/**
 * _strcspn - gets location of s2 within s1
 * @s1: string one
 * @s2: string two
 * Return: location of first char
 */
unsigned int _strcspn(char *s1, char *s2)
{
	unsigned int len = 0;

	if ((s1 == NULL) || (s2 == NULL))
		return (len);

	while (*s1)
	{
		if (_strchr(s2, *s1))
		{
			return (len);
		}
		else
		{
			s1++;
			len++;
		}
	}
	return (len);
}
