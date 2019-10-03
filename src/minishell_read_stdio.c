/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_read_stdio.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:06:22 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/03 21:56:49 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tmp(int sig)
{
	if (sig == SIGINT)
	{
		// ft_printf("hello\n");
		ft_printf("\n");
		// system("clear");
		minishell_greeting(getenv("HOME"));
	}
}

char	*minishell_read_stdio(void)
{
	char	*read_stdio;
	int		stat_gnl;

	signal(SIGINT, tmp);
	if ((stat_gnl = get_next_line(STDIN, &read_stdio, FLAG_OFF)) == RET_ERROR)
		err_exit(E_MALLOC, "minishell");
	signal(SIGINT, tmp);
	return (read_stdio);
}
