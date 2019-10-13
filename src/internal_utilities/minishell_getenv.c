/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_getenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 23:12:07 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/13 22:51:16 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

char		*minishell_getenv(const char *name)
{
	char	**p_env;
	char	*p_ret;
	size_t	len_name;

	p_env = NULL;
	p_ret = NULL;
	if (name && *name)
	{
		len_name = ft_strnlen(name, '=');
		p_env = environ;
		while (*p_env)
		{
			if (!ft_memcmp(name, *p_env, len_name) &&
				*((*p_env) + len_name) == '=')
			{
				p_ret = ft_strchr(*p_env, '=') + 1;
				break ;
			}
			++p_env;
		}
	}
	return (p_ret);
}
