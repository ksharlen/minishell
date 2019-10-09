/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_utilities.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 15:20:33 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/09 17:03:15 by ksharlen         ###   ########.fr       */
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

# define P_ARGS_UNUSED(...) (void)(__VA_ARGS__)

enum	e_u_err
{
	FAILURE = -1,
	SUCCESS
};

/*
**ENV
*/
# define ENV_PRINT(err, filename) ft_printf("env: %s: %s\n", filename, err)
# define ENV_OPT "P:i:u:S:"
# define USG	"usage: env [-iv] [-P utilpath] [-S string] [-u name]"
# define USG_1	"[name=value ...] [utility [argument ...]]"
# define ENV_ERR(err, filename) ft_printf("env: %s: %s\n", filename, err)
# define ERR_EXT(err, filename) ENV_ERR; exit(EXIT_FAILURE)
# define F_P 1
# define F_I 2
# define F_U 4
# define F_S 8

/*
**ECHO
*/
# define ECHO_OPT "n"

/*
**CD
*/
# define CD_TOO_MANY S_TOO_MANY
# define CD_ERR(err, filename) ft_printf("cd: %s %s\n", err, filename)
# define EMPTY_STR ""
# define PATH argv[1]
# define N_TOO_LONG "File name too long"
# define NOT_DIR	"Not a directory"

typedef unsigned char t_opts;

struct	s_nameval
{
	char	*name;
	char	*value;
};

typedef struct	s_env
{
	t_opts		opt;
	char		*path_exec;
	char		*path_dflt;
	char		*cmd;
	char 		**cmd_argv;
}				t_env;

int					minishell_pwd(int argc, char **argv, char **env);
int					minishell_setenv(const char *name, const char *value, const int replace);
int					minishell_unsetenv(const char *name);
int					minishell_echo(int argc, char **argv, char **env);
int					minishell_cd(int argc, char **argv, char **env);

char				**find_var_env(const char *name);
int					minishell_env(int argc, char **argv, char **env);
void				work_opt(char *const *p_argv, t_env *env);
char				**split_s_key(const char *str);


/*
**WORK_FLAGS
*/
char *const			*u_flag(char *const argv[]);
char				**s_flag(const char *str);
char *const			*change_value_name(char *const argv[]);
struct s_nameval	split_name_val(const char *nameval);

#endif