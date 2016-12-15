#include "shell.h"
/**
 * main - Holberton Shell
 */
int main(int argc, char **argv, char **envp)
{
	char *buf, *cmd, *path;
	char **arg_list, **search_path;
	env_t *env_p;
	int j;
	(void)argv, (void)envp, (void)argc;

	env_p = create_envlist();
	cmd = safe_malloc(sizeof(char) * BUFSIZE);
	path = safe_malloc(sizeof(char) * BUFSIZE);
	buf = NULL;
	search_path = NULL;
	arg_list = NULL;
	while (1)
	{
		print_cmdline();
		buf = _getline(buf);
		strncat(buff, "\0", 1);
		tokenize_buf(buf, &arg_list);
		if (arg_list[0] == NULL)
			continue;
		strcpy(cmd, arg_list[0]);
		if(!run_builtin(arg_list, env_p))
			continue; /* need to pass more args than this! */
		else if (strchr(cmd, '/') != NULL)
			execute_func(cmd, arg_list);
		else
		{
			get_path(path, env_p);
			search_path = tokenize_path(search_path, path);
			if (create_path(cmd, search_path) == 0)
			{
				execute_func(cmd, arg_list);
			}
		}
		memset(buf, '\0', 100);
	}
/*	printf("%s\n", buff);*/
	return (0);
}
void execute_func(char *cmd, char **args)
{
	int status, i;

	if (fork() == 0)
	{
		i = execve(cmd, args, NULL);
		if (i < 0)
		{
			write (0, "Error: command not found\n", 25);
			exit(1);
		}
	}
	else
		wait(&status);
}