/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 22:59:27 by rloraine          #+#    #+#             */
/*   Updated: 2019/10/02 21:20:40 by rloraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pwd(int argc, char *argv[], char *env[])
{
	char	*tmp;
	int		n;

	P_UNUSED(argv);
	P_UNUSED(argc);
	n = -1;
	while (env[++n])
		if (ft_strstr(env[n], "PWD"))
			tmp = ft_strdup(ft_strchr(env[n], '/'));//!need to defense
	ft_printf("%s\n", tmp);
	free(tmp);
	return (0);
}
