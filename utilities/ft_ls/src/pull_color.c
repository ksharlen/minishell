/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pull_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 14:58:02 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/17 09:56:22 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static const char	*def_style(const char *ls_color, const ssize_t index_color)
{
	char *color;
	char sym;

	sym = 0;
	color = ft_strnew(sizeof(char) * 11);
	if (!color)
		sys_errors();
	if (ls_color)
		sym = *(ls_color + index_color);
	def_color(color, sym);
	if (ls_color)
		sym = *(ls_color + index_color + 1);
	def_backgrnd(color, sym);
	if (ls_color)
		sym = *(ls_color + index_color);
	def_font(color, sym);
	return (color);
}

static const char	*color_dir(mode_t st_mode, const char *ls_color)
{
	const char *color;

	if (st_mode & O_W)
	{
		if (st_mode & S_ISVTX)
			color = def_style(ls_color, DSCKB);
		else
			color = def_style(ls_color, DSCKNB);
	}
	else
		color = def_style(ls_color, DIRF);
	return (color);
}

static const char	*color_stdf_or_ex(mode_t st_mode, const char *ls_color)
{
	const char *color;

	if ((st_mode & U_X) || (st_mode & G_X) || (st_mode & O_X))
		color = def_style(ls_color, EX);
	else
		color = def_style(NULL, 0);
	return (color);
}

static const char	*push_color_for_spec_file(mode_t st_mode,
	const char *ls_color)
{
	const char *color;

	if (st_mode & S_ISUID)
		color = def_style(ls_color, SUID);
	else if (st_mode & S_ISGID)
		color = def_style(ls_color, SGID);
	else if (st_mode & S_ISVTX)
		color = def_style(ls_color, DSCKB);
	else if (st_mode & S_IXGRP)
		color = def_style(ls_color, DSCKNB);
	else
		color = def_style(NULL, 0);
	return (color);
}

const char			*push_color(const mode_t st_mode, const char *ls_color)
{
	const char *color;

	if (S_ISDIR(st_mode))
		color = color_dir(st_mode, ls_color);
	else if (S_ISLNK(st_mode))
		color = def_style(ls_color, LINK);
	else if (S_ISSOCK(st_mode))
		color = def_style(ls_color, SOCKET);
	else if (S_ISFIFO(st_mode))
		color = def_style(ls_color, PIPE);
	else if (S_ISREG(st_mode))
		color = color_stdf_or_ex(st_mode, ls_color);
	else if (S_ISBLK(st_mode))
		color = def_style(ls_color, BLKF);
	else if (S_ISCHR(st_mode))
		color = def_style(ls_color, SYMF);
	else
		color = push_color_for_spec_file(st_mode, ls_color);
	return (color);
}
