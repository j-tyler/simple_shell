#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 1024
#define ARGLISTINIT 5
/**
 * struct builtin - lookup structure for builtin functions
 * @name: string name user types to call function
 * @func: function pointer to that function
 */
typedef struct builtin
{
	char *name;
	void (*func)();
} builtin;

extern char **environ;

/* helpers.c */
void print_cmdline();
int _strlen(char *s);
int _str_match(char *s1, char *s2);
void free_args(char **arg_list);
void execute_func(char *cmd, char **args);

/* path_funcs.c */
void get_path(char *path);
char **tokenize_path(char **search_path, char *path);
/* tokenize.c */
void tokenize_buf(char *buf, char ***av);
void _av_init(char *buf, char ***av);
int _is_whitespace(char c);
/* builtin.c */
int run_builtin(/* wat we doing here? */);
#endif
