/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_execution.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:44:51 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/25 20:20:58 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_command_execution(t_argv *beg, char *const env[])
{
	pid_t 	pid;
	int		status_child;
	char	*path_ex;

	path_ex = NULL;
	while (beg)
	{
		pid = fork();
		if (!pid)
		{
			//path_ex = ft_strjoin("/bin/", beg->argv[0]);
			path_ex = ft_strjoin(FULL_PATH, beg->argv[0]);
			ft_printf("path_ex: %s\n", path_ex);
			execve(path_ex, beg->argv, env);
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(&status_child);
		}
		//exit(EXIT_SUCCESS);
		beg = beg->next;
	}
}
