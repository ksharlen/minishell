/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 22:59:27 by rloraine          #+#    #+#             */
/*   Updated: 2019/10/01 23:08:30 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pwd(int argc, char *const *argv[], char *const env[])
{
	char	*tmp;
	int		n;

	P_UNUSED(argv);
	P_UNUSED(argc);
	n = -1;
	while (env[++n])
		if (ft_strstr(env[n], "PWD"))
			tmp = ft_strdup(ft_strchr(env[n], '/'));
	ft_printf("%s\n", tmp);
	return (0);
}
