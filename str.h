#ifndef _str_h
#define _str_h
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


void correct_path(char (*use_path)[1024], char *path);
int _strncmp(const char *s1, const char *s2, size_t n);
unsigned int _strcspn(char *s1, char *s2);
char *_strchr(char *s, char c);
char *_strdup(char *src);
void _printenv(void);
void _cd_logic(char *dest);
int _strlen(const char *s);
char *_strncpy(char *destination, const char *source, size_t num);
char *_strcat(char *destination, const char *source);
void tostring(char str[], int num);
void handle_token(char *line, char **argv, int *i);

#endif
