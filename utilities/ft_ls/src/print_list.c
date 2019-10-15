/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 09:55:09 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/13 20:48:10 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*insert_color_filename(const char *filename,
	const char *color)
{
	char *color_filename;
	char *free_string;

	color_filename = ft_strjoin(color, filename);
	CHECK_ALLOC(color_filename);
	free_string = color_filename;
	color_filename = ft_strjoin(color_filename, DEFAULT_STYLE);
	CHECK_ALLOC(color_filename);
	ft_strdel(&free_string);
	ft_strdel((char **)&color);
	return (color_filename);
}

static t_len	large_filename(t_filename *beg)
{
	t_len	len_filename;
	t_len	large_filename;

	len_filename = 0;
	large_filename = 0;
	while (beg)
	{
		if ((len_filename = ft_strlen(beg->filename)) > large_filename)
			large_filename = len_filename;
		beg = beg->next;
	}
	return (large_filename);
}

static char		**get_files(t_filename *begin, const char *ls_color)
{
	size_t		len_files;
	char		**files;
	char		**p_files;
	const char	*color;

	files = NULL;
	len_files = pull_size_list(begin);
	files = (char **)ft_memalloc(sizeof(char *) * (len_files + 1));
	p_files = files;
	while (begin)
	{
		color = push_color(begin->buf->st_mode, ls_color);
		*p_files = insert_color_filename(begin->filename, color);
		++p_files;
		begin = begin->next;
	}
	column(len_files, files);
	return (files);
}

static void		simple_print_lists(t_filename *beg,
	const char *ls_color)
{
	int			len_max_filename;
	char		**files;
	t_filename	*begin;

	begin = beg;
	len_max_filename = large_filename(beg) + (11 * 2);
	files = get_files(begin, ls_color);
	ft_strdel_split(files);
	free(files);
}

void			print_list(t_filename *beg, t_ubyte *flags)
{
	char	*ls_color;

	ls_color = getenv("LSCOLORS");
	if (!ls_color)
	{
		ls_color = (char[SIZE_BUF]){0};
		ft_strcpy(ls_color, "Gxfxcxdxbxegedabagacad");
	}
	if (beg)
	{
		if (chk_flags_for_print_fullinfo(flags) == TRUE)
			print_fullinfo(beg, flags, ls_color);
		else
			simple_print_lists(beg, ls_color);
	}
}
