/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_execution.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:44:51 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/27 15:23:06 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static enum e_find	main_search_cmd(const char *cmd_name, char *cmd_for_ex)
// {
// 	enum e_find	search_cmd;

// 	search_cmd = NOT_FOUND;
// 	if (cmd_name && *cmd_name && cmd_for_ex)
// 	{
// 		ft_bzero(cmd_for_ex, MAX_UNAME + 1);
// 		if ((search_cmd = minishell_command_execution))
// 	}
// }

void	minishell_command_execution(t_argv *beg, char *const env[])
{
	enum e_find	search;
	char cmd_for_ex[MAX_UNAME + 1];

	P_UNUSED(env);
	while (beg)
	{
		search = minishell_command_search(beg->CMD_NAME, cmd_for_ex);
		if (search == FOUND_INTERNAL_CMD)
			;//empty
		else if (search == FOUND_SHELL_DIR)
			;
		else if (search == FOUND_PATH_ENV)
			;
		else
			CMD_NOT_FOUND(beg->CMD_NAME);
		beg = beg->next;
	}
}


// void	minishell_command_execution(t_argv *beg, char *const env[])
// {
// 	pid_t	pid;
// 	int		status_child;
// 	char	path_ex[MAX_SIZE_PATH + 1];
// 	int		ret_execve;

// 	while (beg)
// 	{
// 		if (minishell_command_search(beg->argv[0], path_ex) == NOT_FOUND)
// 			CMD_NOT_FOUND(beg->argv[0]);
// 		else
// 		{
// 			pid = NEW_PROCESS();
// 			if (!pid)
// 			{
// 				ret_execve = execve(path_ex, beg->argv, env);
// 				if (ret_execve == NOT_FOUND)
// 					CMD_NOT_FOUND(beg->argv[0]);
// 				else
// 					exit(EXIT_SUCCESS);
// 			}
// 			else
// 				wait(&status_child);
// 		}
// 		beg = beg->next;
// 	}
// }
