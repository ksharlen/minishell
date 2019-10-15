/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_filename.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 09:49:38 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/18 06:47:24 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				list_revers(t_filename **beg)
{
	t_filename *curr;
	t_filename *next;
	t_filename *prev;

	curr = (*beg);
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	(*beg) = prev;
}

t_filename			*list_filename_merge(t_filename *l_one, t_filename *l_two,
	int (*key)(t_filename *, t_filename *))
{
	t_filename tmp;
	t_filename *new;
	t_filename *res;

	new = &tmp;
	res = new;
	while (l_one && l_two)
	{
		if (key(l_one, l_two) > 0)
		{
			res->next = l_one;
			res = l_one;
			l_one = l_one->next;
		}
		else
		{
			res->next = l_two;
			res = l_two;
			l_two = l_two->next;
		}
	}
	res->next = (l_one ? l_one : l_two);
	return (new->next);
}

static t_filename	*list_filename_create(const char *filename,
	uint8_t f_type, const char *dirname)
{
	t_filename	*new;

	new = (t_filename *)ft_memalloc(sizeof(t_filename));
	if (!new)
		sys_errors();
	new->filename = ft_strdup(filename);
	new->f_type = f_type;
	new->dirname = dirname;
	new->path = cat_path_filename(new->dirname, new->filename);
	new->next = NULL;
	new->buf = NULL;
	return (new);
}

void				list_filename_add_end(t_filename **beg,
	const char *filename, uint8_t f_type, const char *dirname)
{
	t_filename	*res;
	t_filename	*new;

	new = list_filename_create(filename, f_type, dirname);
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

void				push_list_filename_dir_content(DIR *dir, t_filename **beg,
	t_ubyte *flags, const char *dirname)
{
	struct dirent *dent;

	while ((dent = valid_readdir(dir)))
	{
		if (flags[FIND_FLAG('f')] || flags[FIND_FLAG('a')])
			list_filename_add_end(beg, dent->d_name, dent->d_type, dirname);
		else
		{
			if (!ft_strncmp(dent->d_name, ".", 1))
				;
			else
				list_filename_add_end(beg, dent->d_name, dent->d_type, dirname);
		}
	}
}
