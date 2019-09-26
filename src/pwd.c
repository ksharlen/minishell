/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 22:59:27 by rloraine          #+#    #+#             */
/*   Updated: 2019/09/26 23:17:21 by rloraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char *const *argv[], char *const env[])
{
	char	*tmp;
	int		n;

	P_UNUSED(argv);
	n = -1;
	while (env[++n])
		if (ft_strstr(env[n], '"PWD'))
			tmp = ft_strdip(ft_strchr(env[n], '/'));
	ft_printf("%s\n", tmp);
}
