/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_execution.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:44:51 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/01 14:42:52 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//!BEGIN_TMP!!!!
	static int	cd(int argc, char *argv[], char *enval[])
	{
		P_UNUSED(argc);
		P_UNUSED(argv);
		P_UNUSED(enval);
		chdir(argv[1]);
		return (0);
	}

	static int	echo(int argc, char *argv[], char *enval[])
	{
		P_UNUSED(argc);
		P_UNUSED(argv);
		P_UNUSED(enval);
		return (0);
	}

	static int	env(int argc, char *argv[], char *enval[])
	{
		P_UNUSED(argc);
		P_UNUSED(argv);
		P_UNUSED(enval);
		return (0);
	}

	static int	setenv_internal(int argc, char *argv[], char *enval[])
	{
		P_UNUSED(argc);
		P_UNUSED(argv);
		P_UNUSED(enval);
		return (0);
	}

	static int	unsetenv_internal(int argc, char *argv[], char *enval[])
	{
		P_UNUSED(argc);
		P_UNUSED(argv);
		P_UNUSED(enval);
		return (0);
	}

	static int	exit_internal(int argc, char *argv[], char *enval[])
	{
		P_UNUSED(argc);
		P_UNUSED(argv);
		P_UNUSED(enval);
		exit(EXIT_SUCCESS);
		return (0);
	}
//!END_TMP!!!!

static void	execute_internal_cmd(char *const argv[], char *const enval[], int argc, const char *cmd)
{
	int	(*internal_cmd[NUM_INTERNAL_CMDS])(int argc, char *argv[], char *enval[]);

	internal_cmd[0] = cd;
	internal_cmd[1] = echo;
	internal_cmd[2] = env;
	internal_cmd[3] = setenv_internal;
	internal_cmd[4] = unsetenv_internal;
	internal_cmd[5] = exit_internal;

	internal_cmd[ft_atoi(cmd)](argc, (char **)argv, (char **)enval);
}

void	tmp(int sig)
{
	P_UNUSED(sig);
	ft_printf("minishell: segmentation fault\n");
	// exit(EXIT_SUCCESS);
}

static void execute_cmd(char *const argv[], char *const env[], const char *path_cmd)
{
	pid_t	pid;
	int		status_child;

	signal(SIGSEGV, tmp);
	pid = NEW_PROCESS();
	if (pid == CHILD_PROCESS)
	{
		if (execve(path_cmd, argv, env) == NOT_FOUND)
			CMD_NOT_FOUND(CMD_NAME);
		else
		{
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		wait(&status_child);
	}
}

int		minishell_command_execution(t_argv *beg, char *const env[])
{
	enum e_find	search;
	char		cmd_for_ex[MAX_UNAME + 1];

	while (beg)
	{
		search = minishell_command_search(beg->CMD_NAME, cmd_for_ex);
		if (search == FOUND_EXIT)
			return (FOUND_EXIT);
		else if (search == FOUND_INTERNAL_CMD)
			execute_internal_cmd(beg->argv, env, beg->argc, cmd_for_ex);
		else if (search == FOUND_SHELL_DIR || search == FOUND_PATH_ENV)
			execute_cmd(beg->argv, env, cmd_for_ex);
		else
			CMD_NOT_FOUND(beg->CMD_NAME);
		beg = beg->next;
	}
	return (search);
}
