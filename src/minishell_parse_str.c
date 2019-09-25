/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:18:39 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/24 22:09:52 by ksharlen         ###   ########.fr       */
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
		parsed_str = SPLIT_COMMANDS((char *)str_for_parse, COMMAND_SPLIT);
	ptr_parsed_str = parsed_str;
	while (*ptr_parsed_str)
	{
		list_add_end(&beg, *ptr_parsed_str);
		++ptr_parsed_str;
	}
	return (beg);
}
