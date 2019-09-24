/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:18:39 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/24 15:35:58 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**minishell_parse_str(const char *str_for_parse)
{
	char	**parsed_str;

	parsed_str = NULL;
	if (str_for_parse && *str_for_parse)
		parsed_str = SPLIT_COMMANDS((char *)str_for_parse, COMMAND_SPLIT);
	return (parsed_str);
}
