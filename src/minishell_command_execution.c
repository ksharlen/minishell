/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_execution.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:44:51 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/27 15:58:28 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//!BEGIN_TMP!!!!
	static int	cd(char *argv[], char *enval[])
	{
		P_UNUSED(argv);
		P_UNUSED(enval);
		chdir(argv[1]);
		return (0);
	}

	static int	echo(char *argv[], char *enval[])
	{
		P_UNUSED(argv);
		P_UNUSED(enval);
		return (0);
	}

	static int	env(char *argv[], char *enval[])
	{
		P_UNUSED(argv);
		P_UNUSED(enval);
		return (0);
	}

	static int	setenv_internal(char *argv[], char *enval[])
	{
		P_UNUSED(argv);
		P_UNUSED(enval);
		return (0);
	}

	static int	unsetenv_internal(char *argv[], char *enval[])
	{
		P_UNUSED(argv);
		P_UNUSED(enval);
		return (0);
	}

	static int	exit_internal(char *argv[], char *enval[])
	{
		P_UNUSED(argv);
		P_UNUSED(enval);
		exit(EXIT_SUCCESS);
		return (0);
	}
//!END_TMP!!!!

static void	execute_internal_cmd(char *const argv[], char *const enval[], const char *cmd)
{
	int	(*internal_cmd[NUM_INTERNAL_CMDS])(char *argv[], char *enval[]);

	internal_cmd[0] = cd;
	internal_cmd[1] = echo;
	internal_cmd[2] = env;
	internal_cmd[3] = setenv_internal;
	internal_cmd[4] = unsetenv_internal;
	internal_cmd[5] = exit_internal;

	internal_cmd[ft_atoi(cmd)]((char **)argv, (char **)enval);
}

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
			execute_internal_cmd(beg->argv, env, cmd_for_ex);//empty
		else if (search == FOUND_SHELL_DIR || search == FOUND_PATH_ENV)
			execute_cmd(beg->argv, env, cmd_for_ex);
		else
			CMD_NOT_FOUND(beg->CMD_NAME);
		beg = beg->next;
	}
}
