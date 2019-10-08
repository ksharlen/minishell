/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_execution.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:44:51 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/08 20:35:38 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handler_exec(int sig)
{
	P_UNUSED(sig);
	strsignal(SIGSEGV);
	exit(EXIT_SUCCESS);
}

static void	execute_internal_cmd(char *const argv[],
	int argc, const char *cmd)
{
	P_UNUSED(argv);
	P_UNUSED(argc);
	P_UNUSED(cmd);
	int (*internal_cmd[NUM_INTERNAL_CMDS])(int argc, char *argv[], char *env[]);

	// internal_cmd[0] = cd;
	internal_cmd[1] = minishell_echo;
	internal_cmd[2] = minishell_env;
	internal_cmd[3] = minishell_pwd;
	internal_cmd[ft_atoi(cmd)]((int)argc, (char **)argv, environ);
}

void		execute_cmd(char *const argv[], const char *path_cmd)
{
	pid_t	pid;
	int		status_child;

	if ((pid = NEW_PROCESS()) == RET_ERROR)
		err_exit(E_FORK, "minishell");
	if (pid == CHILD_PROCESS)
	{
		signal(SIGSEGV, handler_exec);
		if (execve(path_cmd, argv, environ) == NOT_FOUND)
			CMD_NOT_FOUND(CMD_NAME);
		else
			exit(EXIT_SUCCESS);
	}
	else if (wait(&status_child) == RET_ERROR)
		err_exit(E_WAIT, "minishell");
}

int			minishell_command_execution(t_argv *beg)
{
	enum e_find	search;
	char		cmd_for_ex[MAX_UNAME + 1];

	while (beg)
	{
		search = minishell_command_search(beg->CMD_NAME, cmd_for_ex);
		if (search == FOUND_EXIT)
			return (FOUND_EXIT);
		else if (search == FOUND_INTERNAL_CMD)
			execute_internal_cmd(beg->argv, beg->argc, cmd_for_ex);
		else if (search == FOUND_SHELL_DIR || search == FOUND_PATH_ENV)
			execute_cmd(beg->argv, cmd_for_ex);
		else
			CMD_NOT_FOUND(beg->CMD_NAME);
		beg = beg->next;
	}
	return (search);
}
