/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:18:39 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/26 19:38:51 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_argv	*minishell_parse_str(const char *str_for_parse)
{
	t_argv	*beg;
	char	**parsed_str;
	char	**ptr_parsed_str;

	beg = NULL;
	parsed_str = NULL;
	if (str_for_parse && *str_for_parse)
	{
		parsed_str = SPLIT_COMMANDS((char *)str_for_parse, COMMAND_SPLIT);
		ptr_parsed_str = parsed_str;
		while (*ptr_parsed_str)
		{
			list_add_end(&beg, *ptr_parsed_str);
			++ptr_parsed_str;
		}
		ft_strdel_split(parsed_str);
		free(parsed_str);
		//ft_strdel((char **)&str_for_parse);
		//ft_strdel(parsed_str);
		//temp(&parsed_str);
		get_next_line(STDIN, NULL, FLAG_ON);
	}
	return (beg);
}
