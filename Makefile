# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/22 10:29:34 by ksharlen          #+#    #+#              #
#    Updated: 2019/10/14 21:41:12 by ksharlen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					:= minishell
DIR_SRC					:= src/
DIR_SRC_UTILITES		:= src/internal_utilities src/internal_utilities/minishell_env
DIR_INCLUDE_MINISHELL	:= ./include
DIR_LIBFT				:= ./libft/
DIR_INCLUDE_LIBFT		:= ./libft/include
DIR_BIN					:= bin/
DIR_LS					:= ./utilities/ft_ls
DIRS_INCLUDE			:= $(DIR_INCLUDE_MINISHELL) $(DIR_INCLUDE_LIBFT) $(DIR_UTILITIES)

SRCS					:=	main.c\
								minishell_greeting.c\
								minishell_read_stdio.c\
								minishell_parse_str.c\
								minishell_command_execution.c\
								minishell_list.c\
								minishell_garbage_collector_internal.c\
								minishell_command_search.c\
								minishell_command_search_path_env.c\
								minishell_push_minishell_history.c\
								minishell_init.c\
								minishell_errors.c\
								minishell_pwd.c\
								minishell_setenv.c\
								minishell_unsetenv.c\
								minishell_env.c\
								operation_env.c\
								work_env.c\
								minishell_echo.c\
								minishell_cd.c\
								minishell_cd_home_dir.c\
								minishell_signals.c\
								minishell_getenv.c\
								minishell_geters.c\
								env_tools.c


OBJS					:= $(SRCS:.c=.o)
OBJS_WITH_DIR			:= $(addprefix $(DIR_BIN), $(OBJS))
HEADERS					:= minishell.h internal_utilities.h
LIBFT					:= libft.a

CFLAGS					:= -Wextra -Werror -Wall -g
CFLAG 					:= -c
NFLAG					:= -o
IFLAG					:= -I
CC						:= gcc

MAKE_LIBFT				:= make -C $(DIR_LIBFT)
MAKE_LS					:= make -C $(DIR_LS)
REMOVE					:= rm -rf

vpath %.c $(DIR_SRC) $(DIR_SRC_UTILITES)
vpath %.o $(DIR_BIN)
vpath %.h $(DIR_INCLUDE_MINISHELL)
vpath %.a $(DIR_LIBFT)

all: make_other $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS_WITH_DIR) $(NFLAG) $@ $(DIR_LIBFT)$(LIBFT) -framework CoreFoundation

$(OBJS): %.o:%.c $(HEADERS) | $(DIR_BIN)
	$(CC) $(CFLAG) $(CFLAGS) $< $(addprefix $(IFLAG), $(DIRS_INCLUDE)) $(NFLAG) $(DIR_BIN)$@

$(DIR_BIN):
	mkdir -p $@

make_other:
	$(MAKE_LIBFT)
	$(MAKE_LS)

clean:
	$(REMOVE) $(OBJS_WITH_DIR)
	$(REMOVE) $(DIR_BIN)
	$(MAKE_LIBFT) clean
	$(MAKE_LS) clean

fclean: clean
	$(REMOVE) $(NAME)
	$(MAKE_LIBFT) fclean
	$(MAKE_LS) fclean

re: fclean all

echo:
	echo $(DIR_INCLUDE_MINISHELL)

.PHONY: clean fclean re
.SILENT: all $(NAME) $(OBJS) $(DIR_BIN) $(LIBFT) clean fclean re make_other
