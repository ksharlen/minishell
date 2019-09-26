/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:10:52 by rloraine          #+#    #+#             */
/*   Updated: 2019/09/25 22:35:08 by rloraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MYERROR 1

// void	unset_env(char **argv, char **env)
// {
	
// }

// void	set_env(char **argv, char **env)
// {
	
// }

int		check_comm(t_argv *beg)
{
	
}

void	get_env(t_argv *beg, char **env)
{
	if (!check_comm(beg))
		exit(MYERROR);
}
