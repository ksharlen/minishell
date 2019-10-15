/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pull.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 09:56:59 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/13 19:56:23 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t		pull_size_list(const t_filename *beg)
{
	size_t	len;

	len = 0;
	if (beg)
	{
		while (beg)
		{
			len++;
			beg = beg->next;
		}
	}
	return (len);
}

const char	*pull_date(const t_filename *beg, const t_ubyte *flags)
{
	const char *ret_date;

	ret_date = NULL;
	if (flags[FIND_FLAG('t')])
	{
		if (flags[FIND_FLAG('u')])
			ret_date = cut_date(beg->buf->st_atimespec.tv_sec);
		else
			ret_date = cut_date(beg->buf->st_mtimespec.tv_sec);
	}
	else if (flags[FIND_FLAG('u')])
		ret_date = cut_date(beg->buf->st_atimespec.tv_sec);
	else if (flags[FIND_FLAG('c')])
		ret_date = cut_date(beg->buf->st_ctimespec.tv_sec);
	else
		ret_date = cut_date(beg->buf->st_mtimespec.tv_sec);
	return (ret_date);
}

char		pull_acl_xattr(const char *path)
{
	ssize_t		xattr;
	acl_t		acl;
	acl_type_t	type;
	size_t		option;
	char		ret;

	option = XATTR_NOFOLLOW;
	type = ACL_TYPE_EXTENDED;
	xattr = listxattr(path, NULL, 0, option);
	if (xattr < 0)
		xattr = 0;
	acl = acl_get_file(path, type);
	if (xattr > 0)
		ret = '@';
	else if (acl != NULL)
		ret = '+';
	else
		ret = ' ';
	acl_free(acl);
	return (ret);
}

char		pull_filetype(const mode_t st_mode)
{
	char	filetype;

	if (S_ISLNK(st_mode))
		filetype = 'l';
	else if (S_ISDIR(st_mode))
		filetype = 'd';
	else if (S_ISCHR(st_mode))
		filetype = 'c';
	else if (S_ISBLK(st_mode))
		filetype = 'b';
	else if (S_ISFIFO(st_mode))
		filetype = 'p';
	else if (S_ISSOCK(st_mode))
		filetype = 's';
	else
		filetype = '-';
	return (filetype);
}

const char	*pull_val_link(const char *path_link)
{
	char *filename_from_link;
	char *print_link;

	filename_from_link = valid_readlink(path_link);
	if (filename_from_link)
	{
		print_link = ft_strjoin(" -> ", filename_from_link);
		CHECK_ALLOC(filename_from_link);
	}
	else
		print_link = NULL;
	ft_strdel((char **)&filename_from_link);
	return (print_link);
}
