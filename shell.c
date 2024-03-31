#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "str.h"

/**
 * get_path - returns the path from environment
 * @environ: current environment string
 * @i: tells to get path of PATH or PWD
 * Return: ptr to first char in value of PATH
 */
char *get_path(char **environ, int i)
{
	char **env = environ;

	while (*env != NULL)
	{
		if (_strncmp(*env, "PATH=", 5) == 0 && i == 0)
		{
			return (*env + 5);
		}
		if (_strncmp(*env, "PWD=", 4) == 0 && i == 1)
			return (*env + 4);
		env++;
	}
	return (NULL);
}

/**
 * _which - gets the full path of a command
 * @res: result path
 * @search: word corresponding to command
 * @env: current environment
 * @dup: ptr to boolean val that tells if res was duped or not
 */
void _which(char **res, char *search, char **env, int *dup)
{
	char *path = get_path(env, 0), temp[1024];
	char *token, buf[1024], use_path[1024];
	struct stat st;

	correct_path(&use_path, path);
	if (!path || _strlen(path) == 0)
	{
		*res = NULL;
		return; }
	_strncpy(temp, use_path, sizeof(temp) - 1);
	temp[sizeof(temp) - 1] = '\0';
	if (temp[0] == ':')
		if (stat(search, &st) == 0)
		{
			*res = _strdup(search), *dup = 1;
			return;
		}
	token = strtok(temp, ":");
	while (token != NULL)
	{
		if (_strncmp(token, " ", 1) == 0)
		{
			if (stat(search, &st) == 0)
			{
				*res = _strdup(search), *dup = 1;
				return;
			}
		}
		_strncpy(buf, token, sizeof(buf) - 1);
		buf[sizeof(buf) - 1] = '\0';
		_strcat(buf, "/"), _strcat(buf, search);
		if (stat(buf, &st) == 0)
		{
			*res = _strdup(buf), *dup = 1;
			return;
		}
		else
			token = strtok(NULL, ":");
	}
	*res = "?";
}



/**
 * handle_exit - handle's logic of exiting shell
 * @isPipe: tells the func if it is piped or not
 * @line_n: return value of getline
 * @line: string typed in terminal
 * Return: 1 for exit 0 for continue
 */
int handle_exit(int isPipe, int line_n, char **line)
{
	if (line_n == -1 && !isPipe)
	{
		printf("\n");
		free(*line);
		return (1);
	}
	if (line_n == -1 || ((_strncmp(*line, "exit", 4) == 0) && (*line)[4] == '\n'))
	{
		free(*line);
		return (1);
	}
	return (0);
}

/**
 * print_not_found - prints to stderr
 * @file_name: file name of currect exe
 * @count: number of current command
 */
void print_not_found(char *file_name, int count)
{
	char buf[1024] = "";
	char num[10];

	_strcat(buf, file_name);
	_strcat(buf, ": ");
	tostring(num, count);
	_strcat(buf, num);
	_strcat(buf, ": ");
	/*_strcat(buf, command);*/
	write(2, buf, _strlen(buf));
	fflush(stdout);
}


/**
 * main - function to run shell
 * @argc: number of inputs
 * @argval: values of inputs
 * @env: current environment
 * Return: zero for success
 */
int main(__attribute__((unused)) int argc, char *argval[], char *env[])
{
	char *line = NULL, *res_path, *argv[65], cwd[256];
	int get_line_n, i = 0, status = 0, isPipe, dup = 0, count = 0;
	size_t len;
	struct stat st;

	while (1)
	{
		isPipe = !isatty(STDIN_FILENO), dup = 0, getcwd(cwd, 256), count++;
		if (!isPipe)
			printf("%s$ ", cwd);
		get_line_n = getline(&line, &len, stdin);
		if (handle_exit(isPipe, get_line_n, &line) == 1)
			exit((status % 10));
		if (_strncmp(line, "env", 3) == 0 && line[3] == '\n')
		{
			_printenv();
			continue; }
		if (_strncmp(line, "\n", 1) == 0)
			continue;
		line[_strcspn(line, "\n")] = '\0', handle_token(line, argv, &i);
		res_path = argv[0];
		if (!res_path)
			continue;
		if (_strncmp(argv[0], "cd", 2) == 0)
		{
			_cd_logic(argv[1]);
			continue; }
		if (argv[0][0] != '/' && argv[0][0] != '.')
			_which(&res_path, argv[0], env, &dup);
		if (stat(res_path, &st) != 0 || _strlen(get_path(env, 0)) == 0)
		{
			print_not_found(argval[0], count), write(2, argv[0], _strlen(argv[0]));
			write(2, ": not found\n", 12);
			continue; }
		if (fork() != 0)
			wait(&status);
		else
		{
			if ((execve(res_path, argv, env) == -1))
				print_not_found(argval[0], count), perror(argv[0]), exit(0); }
		if (dup == 1)
			free(res_path); }
	return (0); }
