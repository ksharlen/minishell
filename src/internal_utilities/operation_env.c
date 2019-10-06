/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 00:27:17 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/07 00:42:37 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

char *const	*u_flag(char *const argv[])
{
	char	**split;
	char	**p_split;

	if (argv && *argv)
	{
		split = split_s_key(*argv++);
		p_split = split;
		while (*p_split)
			minishell_unsetenv(*p_split++);
		ft_strdel_split(split);
		free(split);
	}
	return (argv);
}

void	s_flag()
{

}

void	p_flag()
{
	
}