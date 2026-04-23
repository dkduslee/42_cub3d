NAME    = cubexec.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g
AR      = ar rcs

SRCS    = event.c move.c raycast.c render.c
OBJS    = $(patsubst %.c, %.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I ../minilibx-linux -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re