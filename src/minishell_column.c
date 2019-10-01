/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_column.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsandshr <dsandshr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 16:22:14 by dsandshr          #+#    #+#             */
/*   Updated: 2019/10/01 15:01:48 by dsandshr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int		minishel_largest_file(char **files)
{
	int max_file;

	max_file = 0;
	while (*(++files))
	{
		if (max_file < ft_strlen(*files))
			max_file =  ft_strlen(*files);
	}
	return (max_file + 1);
}

void	minishell_column(char **files, int argc)
{
	int size;

	size = minishel_largest_file(files);
	
}

int main(int argc, char *argv[])
{
	minishell_column(argv, argc);
	return 0;
}