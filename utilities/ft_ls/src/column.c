/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 19:46:01 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/13 20:47:16 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			din_alig(char *files, int w_column, int col_cln,
					int col_files)
{
	char		*str;
	char		*buf;
	char		*p_str;

	if (col_cln > 1 && col_files > 1)
	{
		if (!(str = (char *)ft_memalloc(sizeof(char) * w_column + 1)))
			exit(1);
		p_str = str;
		buf = str;
		ft_memset(str, ' ', w_column);
		while (*files)
		{
			*str = *files;
			str++;
			files++;
		}
		write(1, buf, w_column);
		ft_strdel(&p_str);
	}
	else
		ft_printf("%s\n", files);
}

static int			col_files_column(int col_files_cln, int col_cln)
{
	if (col_cln == 0)
		return (1);
	else if (col_files_cln % col_cln > 0)
	{
		col_files_cln /= col_cln;
		col_files_cln++;
	}
	else if (col_cln == 1)
		col_files_cln = 1;
	else
		col_files_cln /= col_cln;
	return (col_files_cln);
}

static int			col_column(int col_column, int w_column)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	col_column = w.ws_col / w_column;
	return (col_column);
}

static int			largest_file(char **files)
{
	size_t			max_file;

	max_file = 0;
	while (*(++files))
	{
		if (max_file < ft_strlen(*files))
			max_file = ft_strlen(*files);
	}
	return (max_file + 1);
}

void				column(int argc, char **files)
{
	t_column		cln;

	cln.col_files_whl = argc - 1;
	cln.width = largest_file(files);
	cln.col = col_column(cln.col, cln.width);
	cln.col_files = col_files_column(argc - 1, cln.col);
	cln.col_iter = 0;
	cln.poz = 1;
	while (cln.col_files_whl)
	{
		din_alig(files[cln.poz], cln.width, cln.col, argc - 1);
		if (cln.col_files < argc - 1)
		{
			if (cln.poz + cln.col_files <= argc - 1)
				cln.poz += cln.col_files;
			else if (cln.poz == argc - 1 || cln.poz + cln.col_files > argc - 1)
			{
				cln.poz = 1 + ++cln.col_iter;
				ft_printf("\n");
			}
		}
		else
			cln.poz++;
		cln.col_files_whl--;
	}
}
