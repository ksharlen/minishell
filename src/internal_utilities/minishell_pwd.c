/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 22:59:27 by rloraine          #+#    #+#             */
/*   Updated: 2019/10/05 15:41:50 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

int		minishell_pwd(int argc, char *argv[], char *env[])
{
	char *pwd;

	P_UNUSED(argv);
	P_UNUSED(env);
	if (argc > 1)
		PWD_ERR(S_TOO_MANY);
	else
	{
		pwd = (char[MAX_SIZE_PATH + 1]){0};
		if (getcwd(pwd, MAX_SIZE_PATH))
		{
			ft_printf("%s\n", pwd);
			return (0);
		}
	}
	return (-1);
}
