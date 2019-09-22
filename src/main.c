#include "minishell.h"

// static void		print_string(char *const ex[])
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (ex[i])
// 	{
// 		ft_printf("str: %s\n", ex[i]);
// 		++i;
// 	}
// }

int		main(int argc, char **argv, char **envp)
{
	pid_t	pid, v_pid;
	char 	*line;
	char	*flags[] = { "a", "-l" };
	int		status;

	P_UNUSED(argc);
	P_UNUSED(argv);
	P_UNUSED(envp);
	while (1)
	{
		ft_printf("$>");
		get_next_line(0, &line);
		pid = fork();
		if (pid == -1)
			{
				perror("not create fork\n");
				exit(EXIT_FAILURE);
			}
		else if (!pid)
		{
			if (execve(line, flags, NULL) == -1)
				ft_printf("minishell: command not found: %s\n", line);
			exit(EXIT_FAILURE);
		}
		else
		{
			do {
				v_pid = waitpid(pid, &status, WUNTRACED);
			}
			while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
	return (0);
}