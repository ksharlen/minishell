/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 09:41:31 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/19 00:29:03 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			get_options(const char *options, t_ubyte *flags)
{
	++options;
	while (*options)
	{
		if (FLAG_VALID(*options))
			flags[(FLAG_LOW_REG(*options) ? (*options - 'a') + 1
			: (*options - 38))] = FLAG_ON;
		else
			flag_error(*(t_ubyte *)options);
		++options;
	}
}

static size_t		push_flags(size_t argc, char *const argv[], t_ubyte *flags)
{
	register size_t i;

	flags[0] = FLAG_ON;
	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1])
	{
		if (argv[i][1])
		{
			get_options(argv[i], flags);
			++i;
		}
		else
			return (i);
	}
	return (i);
}

static void			valid_flags(const t_ubyte *flags)
{
	register size_t	i;
	t_ubyte			sym;

	i = 1;
	while (i < NUM_FLAGS)
	{
		if (flags[i])
			if (!ft_strchr(FLAGS, sym = (i + (i >= 27 ? 38 : 'a' - 1))))
				flag_error(sym);
		++i;
	}
}

int					chk_flags_for_print_fullinfo(t_ubyte *flags)
{
	if (flags[FIND_FLAG('l')] || flags[FIND_FLAG('g')])
		return (TRUE);
	else
		return (FALSE);
}

size_t				collect_flags(size_t argc, char *const argv[],
	t_ubyte *flags)
{
	size_t	skip_opt_argv;

	skip_opt_argv = 0;
	if (CHECK_KEY(argv[1]))
	{
		skip_opt_argv = push_flags(argc, argv, flags);
		valid_flags(flags);
	}
	return (skip_opt_argv);
}
