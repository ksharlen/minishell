/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_execution.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:44:51 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/25 23:20:59 by ksharlen         ###   ########.fr       */
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
			path_ex = ft_strjoin(FULL_PATH, beg->argv[0]);
			execve(path_ex, beg->argv, env);
			//working env
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(&status_child);
		}
		
		ft_strdel(&path_ex);
		beg = beg->next;
	}
}
