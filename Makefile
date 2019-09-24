# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/22 10:29:34 by ksharlen          #+#    #+#              #
#    Updated: 2019/09/24 15:48:27 by ksharlen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					:= minishell
DIR_SRC					:= src/
DIR_INCLUDE_MINISHELL	:= ./include
DIR_LIBFT				:= ./libft/
DIR_INCLUDE_LIBFT		:= ./libft/include
DIR_BIN					:= bin/
DIRS_INCLUDE			:= $(DIR_INCLUDE_MINISHELL) $(DIR_INCLUDE_LIBFT)

SRCS					:= main.c minishell_greeting.c minishell_read_stdio.c minishell_parse_str.c
OBJS					:= $(SRCS:.c=.o)
OBJS_WITH_DIR			:= $(addprefix $(DIR_BIN), $(OBJS))
HEADERS					:= minishell.h
LIBFT					:= libft.a

CFLAGS					:= -Wextra -Werror -Wall -g
CFLAG 					:= -c
NFLAG					:= -o
IFLAG					:= -I
CC						:= gcc

MAKE_LIBFT				:= make -C $(DIR_LIBFT)
REMOVE					:= rm -rf

vpath %.c $(DIR_SRC)
vpath %.o $(DIR_BIN)
vpath %.h $(DIR_INCLUDE_MINISHELL)
vpath %.a $(DIR_LIBFT)

all: $(LIBFT) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS_WITH_DIR) $(NFLAG) $@ $(DIR_LIBFT)$(LIBFT)

$(OBJS): %.o:%.c $(HEADERS) | $(DIR_BIN)
	$(CC) $(CFLAG) $(CFLAGS) $< $(addprefix $(IFLAG), $(DIRS_INCLUDE)) $(NFLAG) $(DIR_BIN)$@

$(DIR_BIN):
	mkdir -p $@

$(LIBFT):
	$(MAKE_LIBFT)

clean:
	$(REMOVE) $(OBJS_WITH_DIR)
	$(REMOVE) $(DIR_BIN)
	$(MAKE_LIBFT) clean

fclean: clean
	$(REMOVE) $(NAME)
	$(MAKE_LIBFT) fclean

re: fclean all

.PHONY: clean fclean re
.SILENT: all $(NAME) $(OBJS) $(DIR_BIN) $(LIBFT) clean fclean re
