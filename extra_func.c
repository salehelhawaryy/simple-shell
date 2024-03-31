#include "str.h"

/**
 * tostring - takes a num and populates string with num
 * @str: given dest string
 * @num: num to convert
 */
void tostring(char str[], int num)
{
	int i, rem, len = 0, n;

	n = num;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	for (i = 0; i < len; i++)
	{
		rem = num % 10;
		num = num / 10;
		str[len - (i + 1)] = rem + '0';
	}
	str[len] = '\0';
}

/**
 * correct_path - takes path with colons and separates it
 * @use_path: result path
 * @path: default path
 */
void correct_path(char (*use_path)[1024], char *path)
{
	int i = 0;
	int j = 0;
	int seen_colon = 0;

	while (path[i])
	{
		if (path[i] != ':')
			(*use_path)[j] = path[i], seen_colon = 0;
		else
		{
			if (seen_colon == 0)
				(*use_path)[j] = path[i], seen_colon = 1;
			else
			{
				(*use_path)[j] = ' ';
				(*use_path)[j + 1] = path[i];
				j++;
			}
		}
		i++;
		j++;
	}
	(*use_path)[j] = '\0';
}

