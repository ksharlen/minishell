/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_read_stdio.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:06:22 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/08 18:14:00 by ksharlen         ###   ########.fr       */
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

static size_t	skip_tabs(const char *str)
{
	size_t len;

	len = 0;
	if (str)
	{
		while (str && *str && !(TABS(*str)))
		{
			++len;
			++str;
		}
	}
	return (len);
}

static void		insert_env(char *buf, const char *read_stdio)
{
	char		buf_env[MAX_SIZE_PATH + 1];
	size_t		len_w;
	char		*val_env;

	while(read_stdio && *read_stdio)
	{
		ft_bzero(buf_env, MAX_SIZE_PATH + 1);
		read_stdio = ft_strscat(buf, (char *)read_stdio, '$');
		//!ПРоверить на конец
		if (read_stdio && *read_stdio)
		{
			len_w = skip_tabs(read_stdio);
			if (len_w)
			{
				ft_strncpy(buf_env, read_stdio, len_w);
				val_env = getenv(buf_env);
				if (val_env)
					ft_strcat(buf, val_env);
				read_stdio += len_w;
			}
		}
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
	insert_env(buf, read_stdio);
	ft_strdel(&read_stdio);
	return (ft_strdup(buf));
}
