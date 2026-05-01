/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 12:20:59 by aylee             #+#    #+#             */
/*   Updated: 2026/05/01 16:40:51 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define KEY_ESC   65307
# define KEY_W     119
# define KEY_S     115
# define KEY_A     97
# define KEY_D     100
# define KEY_LEFT  65361
# define KEY_RIGHT 65363

# define WIDTH      640
# define HEIGHT     480
# define TEX_WIDTH  64
# define TEX_HEIGHT 64

# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_map
{
	char	**grid;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceil_color;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		tex_num;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		screen;
	t_map		map;
	t_player	player;
	t_img		tex[4];
}	t_game;

typedef struct s_arg
{
	t_img	img;
	t_map	map;
	t_player	player;
	t_ray	ray;
	t_game	game;
}	t_arg;

/* render.c */
void	render(t_game *game);
void	draw_ceiling(t_game *game);
void	draw_floor(t_game *game);
void	draw_walls(t_game *game);

/* raycast.c */
void	init_ray(t_game *game, t_ray *ray, int x);
void	calc_step_and_sidedist(t_game *game, t_ray *ray);
void	perform_dda(t_game *game, t_ray *ray);
void	calc_wall_height(t_game *game, t_ray *ray,
			int *line_height, int *draw_start, int *draw_end);
void	draw_wall_column(t_game *game, t_ray *ray,
			int x, int line_height, int draw_start, int draw_end);

/* move.c */
void	move_player(t_game *game, int keycode);
void	rotate_player(t_game *game, int keycode);

/* event.c */
int		handle_key_press(int keycode, t_game *game);
int		handle_window_close(t_game *game);

/* utils (구현 필요 시) */
int		get_pixel_color(t_img *img, int x, int y);
void	put_pixel(t_game *game, int x, int y, int color);

#endif
