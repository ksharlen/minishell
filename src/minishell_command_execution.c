/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_execution.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:44:51 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/24 19:10:22 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_command_execution(char *const commands[])
{
	pid_t 	pid;
	int		status_child;
	char	*comm;

	pid = fork();
	if (!pid)
	{
		// ft_printf("command: %s\n", *commands);
		comm = ft_strjoin("/bin/", *commands);
		execve(comm, NULL, NULL);
		ft_printf("command: %s\n", comm);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(&status_child);
	}
	exit(EXIT_SUCCESS);
}