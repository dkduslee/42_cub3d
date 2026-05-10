NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(MLX_DIR) -g
SRCS = main.c init.c parse.c color_parse.c texture_parse.c mlx_init.c parse_util.c exit_msg.c free.c window.c map.c map_util.c player_parse.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ../Libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ../minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -I$(MLX_DIR)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re