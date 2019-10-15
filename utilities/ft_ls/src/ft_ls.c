/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 09:42:58 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/19 00:29:41 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ls_internal(const char *dirname, t_ubyte *flags)
{
	t_filename		*beg;
	DIR				*dir;
	static size_t	i;

	beg = NULL;
	dir = valid_opendir(dirname);
	if (dir)
	{
		if (FIND_FLAG('R') && i != 0)
			ft_printf("\n%s:\n", dirname);
		push_list_filename_dir_content(dir, &beg, flags, dirname);
		push_buf_stat_to_filename(beg);
		beg = sort_list_by_flags(&beg, flags);
		print_list(beg, flags);
		if ((closedir(dir) == -1))
			sys_errors();
		if (flags[FIND_FLAG('R')])
		{
			++i;
			pull_dir(beg, flags);
		}
		clear_filename(&beg);
	}
}

void			pull_dir(t_filename *beg, t_ubyte *flags)
{
	while (beg)
	{
		if (beg->path && (beg->f_type == D_TYPE) &&
				ft_strcmp(CURRENT_DIR, beg->filename) &&
				ft_strcmp(PREV_DIR, beg->filename))
			ls_internal(beg->path, flags);
		beg = beg->next;
	}
}

static void		print_dir_for_few_argv(const size_t argc,
	char *const argv[], size_t i, t_ubyte *flags)
{
	t_ubyte		flag_prin_d;

	flag_prin_d = (argc - i > 1) ? 1 : 0;
	flags[FIND_FLAG('R')] && argc - i > 1 ? ft_printf("%s:\n", argv[i]) : 0;
	while ((argc - i) > 0)
	{
		if (flag_prin_d && !flags[FIND_FLAG('R')])
			ft_printf("%s:\n", argv[i]);
		ls_internal(argv[i], flags);
		(argc > 2) && (i < argc - 1) &&
			!flags[FIND_FLAG('R')] ? ft_printf("\n") : 0;
		++i;
	}
}

int				ft_ls(const size_t argc, char *const argv[])
{
	t_ubyte			*flags;
	register size_t	i;

	flags = (t_ubyte[NUM_FLAGS]){0};
	if (argc > 1)
	{
		i = collect_flags(argc, argv, flags);
		i = (!i ? ++i : i);
		if (i == argc)
			ls_internal(CURRENT_DIR, flags);
		else
			print_dir_for_few_argv(argc, argv, i, flags);
	}
	else
		ls_internal(CURRENT_DIR, flags);
	return (0);
}
