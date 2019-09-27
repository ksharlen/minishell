/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 21:33:41 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/27 16:02:12 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_argv	*list_create(char *cmd_argv)
{
	t_argv	*new;

	new = NULL;
	if (cmd_argv && *cmd_argv)
	{
		new = (t_argv *)ft_memalloc(sizeof(t_argv));
		if (!new)
			return (NULL);
		new->argv = SPLIT_COMMANDS(cmd_argv, ' ');
		new->argc = ft_lineslen(new->argv);
		new->next = NULL;
	}
	return (new);
}

void			list_add_end(t_argv **beg, char *cmd_argv)
{
	t_argv *res;
	t_argv *new;

	new = list_create(cmd_argv);
	if (beg)
	{
		if (*beg)
		{
			res = (*beg);
			while (res->next)
				res = res->next;
			res->next = new;
		}
		else
			(*beg) = new;
	}
}
