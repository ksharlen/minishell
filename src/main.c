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

// static char		*time_only(void)
// {
// 	time_t t_time;
// 	char *date;

// 	time(&t_time);
// 	date = ctime(&t_time);
// 	date = ft_strsub(date, 12, 7);
// 	return (date);
// }

// int		main(int argc, char **argv, char **envp)
// {
// 	pid_t	pid;
// 	char 	*line;
// 	char	*flags[] = { "a", "-l" };
// 	int		status;
// 	char	*t_time;

// 	P_UNUSED(argc);
// 	P_UNUSED(argv);
// 	P_UNUSED(envp);
// 	while (1)
// 	{
// 		t_time = time_only();
// 		ft_printf("[%s] $>", t_time);
// 		get_next_line(0, &line);
// 		pid = fork();
// 		if (pid == -1)
// 			{
// 				perror("not create fork\n");
// 				exit(EXIT_FAILURE);
// 			}
// 		else if (!pid)
// 		{
// 			//if ((execv(line, flags)) == -1)
// 			if ((execve(line, flags, envp)) == -1)
// 			{
// 				ft_printf("minishell: command not found: %s\n", line);
// 				perror("err: ");
// 			}
// 			exit(EXIT_FAILURE);
// 		}
// 		else
// 		{
// 			do {
// 				waitpid(pid, &status, WUNTRACED);
// 			}
// 			while (!WIFEXITED(status) && !WIFSIGNALED(status));
// 		}
// 	}
// 	return (0);
// }

static void print_string(char *const *str)
{
	size_t		i;

	i = 0;
	if (str && *str)
	{
		while (*str)
		{
			ft_printf("%s\n", str[i]);
			str++;
		}
	}
}

int		main(int argc, char **argv)
{
	P_UNUSED(argc);
	P_UNUSED(argv);
	char	**p_str;

	if (argc == 2)
	{
		p_str = ft_strsplit_skip_space(argv[1], ';');
		print_string(p_str);
		// //ft_printf("p_str: %s\n", p_str);
		//p_str = ft_skip_before(argv[1], ';');
		//ft_printf("p_str: %s\n", p_str);
	}
	return (0);
}
