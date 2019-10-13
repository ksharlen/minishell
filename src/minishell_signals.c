/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 22:05:07 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/13 22:56:44 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ignore_signals(int sig)
{
	(void)sig;
}

void			status_child(int stat_child,
	pid_t pid_child, const char *path_cmd)
{
	char	*lvl_proccess;

	lvl_proccess = minishell_getenv(SHLVL);
	if (!lvl_proccess)
		lvl_proccess = "1";
	if (stat_child == SIGINT)
		ft_printf("\n");
	else if (stat_child == SIGSEGV)
		PRINT_SIG_ERR(lvl_proccess, pid_child, ESIG, path_cmd);
	else if (stat_child == SIGABRT)
		PRINT_SIG_ERR(lvl_proccess, pid_child, EABR, path_cmd);
	else if (stat_child == SIGBUS)
		PRINT_SIG_ERR(lvl_proccess, pid_child, EBUS, path_cmd);
	else if (stat_child == SIGFPE)
		PRINT_SIG_ERR(lvl_proccess, pid_child, FPOT, path_cmd);
	else if (stat_child == SIGQUIT)
	{
		ft_printf("\n");
		PRINT_SIG_ERR(lvl_proccess, pid_child, QUIT, path_cmd);
	}
}

void			handler_parrent(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		ft_printf("\n");
		minishell_greeting();
	}
}

void			handler_child(int sig)
{
	if (sig == SIGINT)
		exit(EXIT_FAILURE);
	else if (sig == SIGQUIT)
		;
}

void			minishell_signals(void (*handler)(int))
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
