/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_setenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:09:07 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/05 16:51:10 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

static char		**find_var_env(const char *name)
{
	size_t		i;

	i = 0;
	while (environ[i])
	{
		if (!ft_memcmp(environ[i], name, ft_strnlen(name, '=')))
			return (&environ[i]);
		++i;
	}
	return (NULL);
}

static int		new_val_name(char **p_name, const char *value, size_t len_name)
{
	char	*tmp;
	char	*buf;

	buf = (char[MAX_SIZE_PATH]){0};
	ft_strncpy(buf, *p_name, len_name);
	buf[len_name] = '=';
	if (*p_name)
	{
		tmp = (*p_name);
		(*p_name) = ft_strjoin(buf, value);
		if (*p_name)
			return (0);
	}
	return (-1);
}

int				minishell_setenv(const char *name, const char *value, int replace)
{
	char **p_name;

	if (name && value && *name)
	{
		p_name = find_var_env(name);
		if (replace)
			new_val_name(p_name, value, ft_strnlen(name, '='));
		return (0);
	}
	return (-1);
}