/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_stat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 09:40:00 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/18 17:50:42 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			add_uname_grname(t_filename *beg)
{
	while (beg)
	{
		beg->pw_name = ft_strdup(getpwuid(beg->buf->st_uid)->pw_name);
		beg->gr_name = ft_strdup(getgrgid(beg->buf->st_gid)->gr_name);
		beg = beg->next;
	}
}

static struct stat	*buf_stat_create(void)
{
	struct stat	*new;

	new = (struct stat *)ft_memalloc(sizeof(struct stat));
	if (!new)
		sys_errors();
	return (new);
}

static void			buf_stat_add_to_filename(t_filename *beg)
{
	if (beg)
	{
		while (beg)
		{
			beg->buf = buf_stat_create();
			beg = beg->next;
		}
	}
}

void				push_buf_stat_to_filename(t_filename *beg)
{
	t_filename	*res;

	res = beg;
	buf_stat_add_to_filename(beg);
	if (beg)
	{
		while (beg)
		{
			valid_stat(beg->path, beg->buf, beg->f_type);
			beg = beg->next;
		}
		add_uname_grname(res);
	}
}
