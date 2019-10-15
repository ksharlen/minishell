/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fullinfo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 09:38:07 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/18 18:47:57 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_long_format_dev(const struct s_print *print_info,
	const struct s_num *align, const dev_t st_rdev)
{
	int32_t	little_init_dev;
	int32_t big_init_dev;
	char	*big_init_dev_str;
	char	sym;

	sym = ((print_info->filetype == 'c' || print_info->filetype == 'b')
		? ',' : ' ');
	little_init_dev = MINOR(st_rdev);
	big_init_dev = MAJOR(st_rdev);
	big_init_dev_str = (print_info->filetype == 'c' ||
		print_info->filetype == 'b') ? ft_itoa(big_init_dev)
		: ft_strsetalloc(' ', align->max_len_big_dev);
	ft_printf("%c%s%c %*d %-*s%-*s %*s%c %*d %s %s%s%s%s\n",
		print_info->filetype, print_info->permission, print_info->acl_xattr,
		align->max_num_link, print_info->num_link, align->max_len_user,
		print_info->user, align->max_len_group, print_info->group,
		align->max_len_big_dev, big_init_dev_str, sym,
		align->max_len_little_dev,
		little_init_dev, print_info->date, print_info->color,
		print_info->filename,
		DEFAULT_STYLE, print_info->val_link);
	ft_strdel(&big_init_dev_str);
}

static void	print_long_format(const struct s_print *print_info,
	struct s_num *align)
{
	ft_printf("%c%s%c %*d %-*s%-*s%*lld %s %s%s%s%s\n",
		print_info->filetype,
		print_info->permission, print_info->acl_xattr, align->max_num_link,
		print_info->num_link, align->max_len_user, print_info->user,
		align->max_len_group, print_info->group, align->max_num_size_file,
		print_info->size_file, print_info->date, print_info->color,
		print_info->filename, DEFAULT_STYLE, print_info->val_link);
}

static void	fill_s_print(const t_filename *beg,
	const t_ubyte *flags, struct s_print *info)
{
	if (info->ls_color)
		info->color = push_color(beg->buf->st_mode, info->ls_color);
	info->filetype = pull_filetype(beg->buf->st_mode);
	if (S_ISLNK(beg->buf->st_mode))
		info->val_link = pull_val_link(beg->path);
	else
		info->val_link = "";
	info->permission = pull_access_permission(beg->buf->st_mode);
	info->acl_xattr = pull_acl_xattr(beg->path);
	info->num_link = beg->buf->st_nlink;
	info->group = beg->gr_name;
	if (flags[FIND_FLAG('g')])
	{
		info->user = info->group;
		info->group = "";
	}
	else
		info->user = beg->pw_name;
	info->size_file = beg->buf->st_size;
	info->date = pull_date(beg, flags);
	info->filename = beg->filename;
}

static void	print_long_line(struct s_print *print_info,
	struct s_num *align, const char *dirname, const dev_t st_rdev)
{
	if (!ft_strcmp(dirname, "dev") || !ft_strcmp(dirname, "/dev"))
		print_long_format_dev(print_info, align, st_rdev);
	else
		print_long_format(print_info, align);
}

void		print_fullinfo(const t_filename *beg,
	const t_ubyte *flags, const char *ls_color)
{
	struct s_print	print_info;
	struct s_num	align;

	print_info.ls_color = ls_color;
	max_len_elem(beg, &align);
	max_len_little_big_dev(beg, &align);
	align.max_len_user += 2;
	align.max_len_group += 2;
	if (flags[FIND_FLAG('g')])
	{
		align.max_len_user = align.max_len_group;
		align.max_len_group = 0;
	}
	ft_printf("total %lld\n", align.total);
	while (beg)
	{
		fill_s_print(beg, flags, &print_info);
		print_long_line(&print_info, &align, beg->dirname, beg->buf->st_rdev);
		beg = beg->next;
		clean_mem(print_info);
	}
}
