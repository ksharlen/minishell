/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:18:39 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/14 21:54:21 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_parsed_str_and_for_parse(char ***parsed, char **for_parse)
{
	if (*parsed && *for_parse)
	{
		free(*parsed);
		free(*for_parse);
		*parsed = NULL;
		*for_parse = NULL;
	}
}

t_argv		*minishell_parse_str(const char *str_for_parse)
{
	t_argv	*beg;
	char	**parsed_str;
	char	**ptr_parsed_str;

	beg = NULL;
	parsed_str = NULL;
	if (str_for_parse && *str_for_parse)
	{
		parsed_str = SPLIT_COMMANDS((char *)str_for_parse, COMMAND_SPLIT);
		if (!parsed_str)
			err_exit(E_MALLOC, "minishell");
		ptr_parsed_str = parsed_str;
		while (*ptr_parsed_str)
		{
			list_add_end(&beg, *ptr_parsed_str);
			++ptr_parsed_str;
		}
		ft_strdel_split(parsed_str);
		del_parsed_str_and_for_parse(&parsed_str, (char **)&str_for_parse);
		get_next_line(STDIN_FILENO, NULL, FLAG_ON);
	}
	return (beg);
}
