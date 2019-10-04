/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_read_stdio.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:06:22 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/04 15:15:13 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		minishell_handler(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		ft_printf("\n");
		minishell_greeting(getenv("HOME"));
	}
}

char			*minishell_read_stdio(void)
{
	char	*read_stdio;
	int		stat_gnl;
	char	*buf;

	buf = (char[ARG_MAX]){0};
	signal(SIGINT, minishell_handler);
	signal(SIGQUIT, minishell_handler);
	if ((stat_gnl = get_next_line(STDIN, &read_stdio, FLAG_OFF)) == RET_ERROR)
		err_exit(E_MALLOC, "minishell");
	// find_symbal('$', read_stdio);
	return (read_stdio);
}
