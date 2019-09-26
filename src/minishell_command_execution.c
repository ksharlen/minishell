/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_execution.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:44:51 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/26 21:17:50 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_command_execution(t_argv *beg, char *const env[])
{
	pid_t	pid;
	int		status_child;
	char	path_ex[MAX_SIZE_PATH + 1];
	int		ret_execve;

	while (beg)
	{
		if (minishell_command_search(beg->argv[0], path_ex) == NOT_FOUND)
			CMD_NOT_FOUND(beg->argv[0]);
		else
		{
			pid = NEW_PROCESS();
			if (!pid)
			{
				ret_execve = execve(path_ex, beg->argv, env);
				if (ret_execve == NOT_FOUND)
					CMD_NOT_FOUND(beg->argv[0]);
				else
					exit(EXIT_SUCCESS);
			}
			else
				wait(&status_child);
		}
		beg = beg->next;
	}
}
