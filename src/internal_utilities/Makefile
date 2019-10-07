NAME	:= main
SRCS	:= main_test.c\
			minishell_cd.c\
			minishell_pwd.c\
			minishell_setenv.c\
			minishell_unsetenv.c\
			minishell_env.c\
			work_env.c\
			operation_env.c\

HEADERS	:= internal_utilities.h

OBJS	:= $(SRCS:.c=.o)

CFLAGS	:= -Wall -Wextra -Werror

vpath %.h ../

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(OBJS) ../../libft/libft.a -o $@

$(OBJS):%.o:%.c $(HEADERS)
	gcc -c $< -I ../../include -I ../../libft/include -I .