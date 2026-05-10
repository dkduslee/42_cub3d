NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I./parse -I./excute -I./Libft -I./minilibx-linux -g
LDFLAGS     = -L./minilibx-linux -lmlx -lXext -lX11 -lm -lbsd

PARSE_DIR   = ./parse/
EXCUTE_DIR  = ./execute/
LIBFT_DIR   = ./Libft/
MLX_DIR     = ./minilibx-linux/

SRC_FILES   = $(PARSE_DIR)color_parse.c $(PARSE_DIR)exit_msg.c $(PARSE_DIR)free.c \
              $(PARSE_DIR)init.c $(PARSE_DIR)map_util.c $(PARSE_DIR)map.c \
              $(PARSE_DIR)mlx_init.c $(PARSE_DIR)parse_util.c $(PARSE_DIR)parse.c \
              $(PARSE_DIR)player_parse.c $(PARSE_DIR)texture_parse.c $(PARSE_DIR)window.c \
              $(EXCUTE_DIR)event.c $(EXCUTE_DIR)move.c $(EXCUTE_DIR)raycast.c \
              $(EXCUTE_DIR)render.c \
              ./main.c

OBJ_FILES   = $(SRC_FILES:.c=.o)
LIBFT       = $(LIBFT_DIR)libft.a
MLX         = $(MLX_DIR)libmlx.a

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT) $(MLX)
	@$(CC) $(OBJ_FILES) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@make -C $(MLX_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	rm -f $(OBJ_FILES)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re