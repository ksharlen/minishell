NAME := curses_tests
SRCS :=		main.c
OBJS := $(SRCS:.c=.o)
HEADERS	:= curses_tests.h

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(OBJS) -o $@ -lncurses

$(OBJS): $(HEADERS)

echo:
	echo $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.SILENT: all $(NAME) $(OBJS) echo clean fclean re