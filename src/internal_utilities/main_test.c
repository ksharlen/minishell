/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:29:05 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/05 16:49:26 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

int		main(void)
{
	int ret_setenv;

	if (minishell_setenv("USER", "testing", 2) == -1)
		ft_printf("error\n");
	return (0);
}