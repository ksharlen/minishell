/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_garbage_collector_internal.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:12:57 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/25 23:08:00 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	argvdel(t_argv **del)
{
	if (del && *del)
	{
		free(*del);
		*del = NULL;
	}
}

static void clean_struct(t_argv **beg)
{
	t_argv	*tmp;

	tmp = NULL;
	while (*beg)
	{
		ft_strdel_split((*beg)->argv);
		ft_strdel((*beg)->argv);
		tmp = (*beg);
		(*beg) = (*beg)->next;
		argvdel(&tmp);
	}
	(*beg) = NULL;
}

void	garbage_collector_internal(t_argv **beg, char **need_free)
{
	if (beg && *beg && need_free && *need_free)
	{
		ft_strdel(need_free);
		clean_struct(beg);
	}
}