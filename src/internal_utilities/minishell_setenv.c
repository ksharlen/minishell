/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_setenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:09:07 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/13 22:46:35 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

size_t			find_var_env(const char *name)
{
	int			i;
	size_t		len_name;

	i = 0;
	while (environ[i] && environ[i][0])
	{
		if ((!ft_memcmp(environ[i], name, len_name = ft_strnlen(name, '='))) && environ[i][len_name] == '=')
			return (i);
		++i;
	}
	return (-1);
}

static int		new_val_name(int index, const char *value, size_t len_name)
{
	char	*tmp;
	char	*buf;
	// static int	num_free;

	buf = (char[MAX_SIZE_PATH]){0};
	ft_strncpy(buf, environ[index], len_name);
	buf[len_name] = '=';
	// ft_strcat(buf, value);
	if (index != -1)
	{
		tmp = environ[index];
		environ[index] = ft_strjoin(buf, value);
		free(tmp);
		if (environ[index])
			return (SUCCESS);
	}
	return (FAILURE);
}

static int		push_new_environ(char **new_environ, size_t size_new_env, const char *name, const char *value)
{
	size_t		i;
	char		*buf;

	i = 0;
	buf = (char[MAX_SIZE_PATH]){0};
	ft_strcpy(buf, name);
	ft_strcat(buf, "=");
	while (i < size_new_env - 1)
	{
		new_environ[i] = ft_strdup(environ[i]);
		if (!new_environ[i])
			return (FAILURE);
		++i;
	}
	new_environ[i] = ft_strjoin(buf, value);
	if (!new_environ)
		return (FAILURE);
	new_environ[size_new_env] = NULL;
	return (SUCCESS);
}

static int		create_new_name_val(const char *name, const char *value)
{
	size_t			len_env;
	char			**new_environ;

	len_env = ft_lineslen(environ) + 1;
	new_environ = (char **)ft_memalloc(sizeof(char *) * (len_env + 1));
	if (!new_environ)
		return (FAILURE);
	push_new_environ(new_environ, len_env, name, value);
	environ = new_environ;
	new_environ = NULL;
	return (SUCCESS);
}

int				minishell_setenv(const char *name, const char *value, const int replace)
{
	int				index;
	// char			**p_name
	enum e_u_err	err;

	err = FAILURE;
	if (name && value && *name)
	{
		index = find_var_env(name);
		if (index != -1)
		{
			if (replace)
			{
				err = new_val_name(index, value, ft_strnlen(name, '='));
				// free(*p_name);
			}
		}
		else
			err = create_new_name_val(name, value);
	}
	return (err);
}
