NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(MLX_DIR) -g
SRCS = main.c init.c parse.c color_parse.c texture_parse.c parse_util.c exit_msg.c free.c window.c map.c map_util.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -I$(MLX_DIR)

$(NAME) : $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

$(MLX) :
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

all : $(NAME)

clean :
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean : clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY : all clean fclean re