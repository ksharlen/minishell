/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_execution.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:44:51 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/26 21:57:36 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void temp(char *const argv[], char *const env[])
{
	cd(argv, env);
}

void	minishell_command_execution(t_argv *beg, char *const env[])
{
	//pid_t		pid;
	//int			status_child;
	// char		path_ex[MAX_SIZE_PATH + 1];
	//int			ret_execve;
	enum e_find	search;

	search = NOT_FOUND;
	while (beg)
	{
		// search = minishell_command_search(beg->argv[0], path_ex);
		// if (search == FOUND_INTERNAL)
		// {
			// ft_printf("YES\n");
			temp(beg->argv, env);
		// 
		//if (minishell_command_search(beg->argv[0], path_ex) == NOT_FOUND)
		//	CMD_NOT_FOUND(beg->argv[0]);
		// else
		// {
		// 	pid = NEW_PROCESS();
		// 	if (!pid)
		// 	{
		// 		ret_execve = execve(path_ex, beg->argv, env);
		// 		if (ret_execve == NOT_FOUND)
		// 			CMD_NOT_FOUND(beg->argv[0]);
		// 		else
		// 			exit(EXIT_SUCCESS);
		// 	}
		// 	else
		// 		wait(&status_child);
		// }
		beg = beg->next;
	}
}
