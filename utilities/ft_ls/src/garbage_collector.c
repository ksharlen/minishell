/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 08:45:08 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/18 19:57:04 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	clear_filename(t_filename **beg)
{
	t_filename *res;

	if (beg && *beg)
	{
		res = (*beg);
		while (res)
		{
			(*beg) = (*beg)->next;
			ft_memdel((void **)&res->buf);
			ft_strdel((char **)&res->filename);
			ft_strdel((char **)&res->path);
			ft_strdel((char **)&res->pw_name);
			ft_strdel((char **)&res->gr_name);
			ft_memdel((void **)&res);
			res = (*beg);
		}
	}
}

void	clean_mem(struct s_print print_info)
{
	ft_strdel((char **)&print_info.color);
	ft_strdel((char **)&print_info.date);
	ft_strdel((char **)&print_info.permission);
	if (*print_info.val_link)
		ft_strdel((char **)&print_info.val_link);
}
