# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/16 09:02:55 by ksharlen          #+#    #+#              #
#    Updated: 2019/10/14 19:44:03 by ksharlen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:=	ft_ls
NEW_NAME			:=	ls
DIR_SRC				:=	src/
DIR_BIN				:=	bin/
DIR_INCLUDE 		:=	include/
CC					:=	gcc
CFLAGS				:=	-g -Wextra -Werror -Wall
HEADERS				:=	libft.h ft_printf.h ft_getopt.h ft_ls.h
SRC					:=	main.c\
							ft_ls.c\
							list_filename.c\
							workdir.c\
							flags.c\
							errors.c\
							list_sort.c\
							buf_stat.c\
							other.c\
							cmp_elem_struct.c\
							print_list.c\
							print_fullinfo.c\
							pull.c\
							pull_color.c\
							pull_permission.c\
							garbage_collector.c\
							work_color.c\
							column.c

OBJS 				:=	$(SRC:.c=.o)
LIBFT				:=	libft.a
DIR_LIBFT			:=	../../libft/
DIR_INCLUDE_LIBFT	:=	../../libft/include

DIRS_INCLUDE		:=	$(DIR_INCLUDE) $(DIR_INCLUDE_LIBFT)

REMOVE				:=	rm -rf
MOVE				:=	mv -f

vpath %.c $(DIR_SRC)
vpath %.o $(DIR_BIN)
vpath %.h $(DIRS_INCLUDE)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(addprefix $(DIR_BIN), $(OBJS)) $(DIR_LIBFT)$(LIBFT) -o $@
	$(MOVE) $(NAME) ../$(NEW_NAME)

$(OBJS):%.o:%.c $(HEADERS) | $(DIR_BIN)
	$(CC) -c $(CFLAGS) $< -o $(DIR_BIN)$@ $(addprefix -I , $(DIRS_INCLUDE))

$(DIR_BIN):
	mkdir -p $@

$(LIBFT):
	make -C $(DIR_LIBFT)

clean:
	$(REMOVE) $(addprefix $(DIR_BIN), $(OBJS))
	$(REMOVE) $(DIR_BIN)

fclean: clean
	$(REMOVE) ../$(NEW_NAME)

re: fclean all

.PHONY: clean fclean all re
.SILENT: all $(NAME) $(OBJS) $(DIR_BIN) $(LIBFT) clean fclean re