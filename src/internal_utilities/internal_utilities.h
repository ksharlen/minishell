/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_utilities.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 15:20:33 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/05 18:39:07 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_UTILITIES_H
# define INTERNAL_UTILITIES_H

# include "minishell.h"

/*
**ERRORS
*/
# define S_NO_SUCH "no such file or directory"
# define S_TOO_MANY "too many arguments"

# define PWD_ERR(err) ft_printf("pwd: %s\n", err)

# define CD_ERR(err, var_name) ft_printf("cd: %s: %s\n", err, var_name)

# define P_ARGS_UNUSED(...) (void)(__VA_ARGS__)

enum	e_u_err
{
	FAILURE = -1,
	SUCCESS
};

int		minishell_pwd(int argc, char **argv, char **env);
int		minishell_setenv(const char *name, const char *value, const int replace);
int		minishell_unsetenv(const char *name);
char	**find_var_env(const char *name);

#endif