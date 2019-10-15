/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 09:48:23 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/18 19:55:15 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_filename	*merge_sort(t_filename *list,
	int (*cmp)(t_filename *, t_filename *), t_filename *until)
{
	t_filename *left;
	t_filename *right;

	if (list == until || !list->next)
		return (list);
	left = list;
	right = left->next;
	while (right && right->next)
	{
		list = list->next;
		right = right->next->next;
	}
	right = list->next;
	list->next = NULL;
	return (list_filename_merge(merge_sort(left, cmp, NULL),
		merge_sort(right, cmp, NULL), cmp));
}

static t_filename	*find_end_repeat(t_filename *beg,
	int (*cmp)(t_filename *, t_filename *))
{
	t_filename *res;

	res = NULL;
	if (beg)
	{
		res = beg;
		while (res->next && !cmp(res, res->next))
			res = res->next;
	}
	return (res);
}

static void			test_repeat(t_filename **beg, struct s_sort *sort,
	int (*cmp)(t_filename *, t_filename *))
{
	sort->end = find_end_repeat(*beg, cmp);
	sort->tmp = sort->end->next;
	sort->end->next = NULL;
	if (sort->begin_list && (sort->begin_list == (*beg)))
		sort->begin_list = merge_sort(*beg, cmp_name, NULL);
	else
	{
		(*beg) = merge_sort(*beg, cmp_name, NULL);
		sort->prev->next = (*beg);
	}
	sort->end = list_end_elem(*beg);
	sort->end->next = sort->tmp;
	(*beg) = sort->end;
	sort->prev = (*beg);
}

static t_filename	*sort_repeat(t_filename *beg, int (*cmp)(t_filename *,
	t_filename *))
{
	struct s_sort sort;

	if (beg)
	{
		sort.begin_list = beg;
		sort.prev = beg;
		while (beg->next)
			if (!cmp(beg, beg->next))
				test_repeat(&beg, &sort, cmp);
			else
			{
				sort.prev = beg;
				beg = beg->next;
			}
		return (sort.begin_list);
	}
	return (NULL);
}

t_filename			*sort_list_by_flags(t_filename **beg, t_ubyte *flags)
{
	if (!flags[FIND_FLAG('f')])
	{
		if (flags[FIND_FLAG('t')])
		{
			if (flags[FIND_FLAG('u')])
			{
				(*beg) = merge_sort(*beg, cmp_atime, NULL);
				(*beg) = sort_repeat(*beg, cmp_atime);
			}
			else
			{
				(*beg) = merge_sort(*beg, cmp_mtime, NULL);
				(*beg) = sort_repeat(*beg, cmp_mtime);
			}
		}
		else
			(*beg) = merge_sort(*beg, cmp_name, NULL);
		if (flags[FIND_FLAG('r')])
			list_revers(beg);
	}
	else
		flags[FIND_FLAG('a')] = 1;
	return (*beg);
}
