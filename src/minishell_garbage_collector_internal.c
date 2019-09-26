/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_garbage_collector_internal.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:12:57 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/26 19:44:04 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		strddel(char ***del)
{
	if (del && *del)
	{
		free(*del);
		**del = NULL;
	}
}

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
		free((*beg)->argv);
		tmp = (*beg);
		(*beg) = (*beg)->next;
		argvdel(&tmp);
	}
	(*beg) = NULL;
}

void	garbage_collector_internal(t_argv **beg)
{
	if (beg && *beg)
	{
		// ft_strdel(&need_free);
		//ft_strdel(need_free);
		//free(need_free);
		//strddel(need_free);
		clean_struct(beg);
	}
}