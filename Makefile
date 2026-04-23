NAME    = cub3D
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g

EXEC_DIR    = ./execute
PARSE_DIR   = ./parse
LIBFT_DIR   = ./Libft
MLX_DIR     = ./mlx

EXEC    = $(EXEC_DIR)/cubexec.a
PARSE   = $(PARSE_DIR)/cubparse.a
LIBFT   = $(LIBFT_DIR)/libft.a
MLX     = $(MLX_DIR)/libmlx.a
MLX_URL = https://github.com/42paris/minilibx-linux.git

all: $(NAME)

$(MLX_DIR):
	git clone $(MLX_URL) $(MLX_DIR)

$(MLX): $(MLX_DIR)
	@echo " [..] | Compiling minilibx.. "
	@$(MAKE) -s -C $(MLX_DIR)
	@echo " [ ok ] | Minilibx ready! "

$(LIBFT):
	@echo " [..] | Compiling libft.. "
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo " [ ok ] | libft ready! "

$(EXEC):
	@echo " [..] | Compiling execute.. "
	@$(MAKE) -s -C $(EXEC_DIR)
	@echo " [ ok ] | execute ready! "

$(PARSE):
	@echo " [..] | Compiling parse.. "
	@$(MAKE) -s -C $(PARSE_DIR)
	@echo " [ ok ] | parse ready! "

$(NAME): $(LIBFT) $(MLX) $(EXEC) $(PARSE)
	$(CC) $(CFLAGS) \
		-L$(EXEC_DIR)  -lcubexec  \
		-L$(PARSE_DIR) -lcubparse \
		-L$(LIBFT_DIR) -lft       \
		-L$(MLX_DIR)   -lmlx      \
		-lXext -lX11 -lm -lz      \
		-o $(NAME)

clean:
	@$(MAKE) -s -C $(EXEC_DIR)  clean
	@$(MAKE) -s -C $(PARSE_DIR) clean
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -s -C $(EXEC_DIR)  fclean
	@$(MAKE) -s -C $(PARSE_DIR) fclean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	-@$(MAKE) -s -C $(MLX_DIR)  clean

re: fclean all

.PHONY: all clean fclean re