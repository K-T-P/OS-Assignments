#include "shell.h"

int execute_args(char **args)
{
	pid_t pid;
	int status;
	char *builtin_func_list[] = {
		"cd",
		"exit",
	};
	int (*builtin_func[])(char **) = {
		&own_cd,
		&own_exit,
	};

	long unsigned int i = 0;
	for (; i < sizeof(builtin_func_list) / sizeof(char *); i++)
	{
		/* if there is a match execute the builtin command */
		if (strcmp(args[0], builtin_func_list[i]) == 0)
		{
			return ((*builtin_func[i])(args));
		}
	}
	
	if(fork()==0){
		execvp(args[0],args);
		exit(0);
	}
	wait(NULL);
	return (-1); // this status code means everything is ok
}