/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_execution.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:44:51 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/26 20:04:07 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_command_execution(t_argv *beg, char *const env[])
{
	pid_t 	pid;
	int		status_child;
	char	path_ex[MAX_SIZE_PATH + 1];
	int		ret_minishell_cmd_search;

	while (beg)
	{
		ret_minishell_cmd_search = minishell_command_search(beg->argv[0], path_ex);
		if (ret_minishell_cmd_search == FOUND_INTERNAL_DIR)
		{
			pid = NEW_PROCESS();
			if (!pid)
			{
				{
					if (execve(path_ex, beg->argv, env) == NOT_FOUND)
						CMD_NOT_FOUND(beg->argv[0]);
					else
						exit(EXIT_SUCCESS);
				}
				//working env
			}
			else
			{
				wait(&status_child);
			}
		}
		else if (ret_minishell_cmd_search == FOUND_PATH_ENV)
		{
			if (execve(path_ex, beg->argv, env) == NOT_FOUND)
				CMD_NOT_FOUND(beg->argv[0]);
			else
				exit(EXIT_SUCCESS);
		}
		else
			CMD_NOT_FOUND(beg->argv[0]);
		beg = beg->next;
	}
}
