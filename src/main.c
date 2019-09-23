#include "minishell.h"

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

// static void print_string(char *const *str)
// {
// 	size_t		i;

// 	i = 0;
// 	if (str && *str)
// 	{
// 		while (*str)
// 		{
// 			ft_printf("%s\n", str[i]);
// 			str++;
// 		}
// 	}
// }

// int		main(int argc, char **argv)
// {

// 	return (0);
// }

static void		temp(const char *path)
{
	chdir(path);
}

int		main(int argc, char **argv, char **env)
{
	char	*temp_line;

	P_UNUSED(argc);
	P_UNUSED(argv);
	P_UNUSED(env);
	system("clear");
	while (1)
	{
		minishell_design();
		get_next_line(0, &temp_line);
		temp(temp_line);
	}
	return (0);
}