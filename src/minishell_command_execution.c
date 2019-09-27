/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_execution.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:44:51 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/27 15:32:08 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void execute_cmd(char *const argv[], char *const env[], const char *path_cmd)
{
	pid_t	pid;
	int		status_child;

	pid = NEW_PROCESS();
	if (pid == CHILD_PROCESS)
	{
		if (execve(path_cmd, argv, env) == NOT_FOUND)
			CMD_NOT_FOUND(CMD_NAME);
		else
			exit(EXIT_SUCCESS);
	}
	else
		wait(&status_child);
}

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
		else if (search == FOUND_SHELL_DIR || search == FOUND_PATH_ENV)
			execute_cmd(beg->argv, env, cmd_for_ex);
		else
			CMD_NOT_FOUND(beg->CMD_NAME);
		beg = beg->next;
	}
}
