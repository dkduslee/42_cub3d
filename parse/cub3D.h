/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:51:21 by solee             #+#    #+#             */
/*   Updated: 2026/04/19 13:34:39 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define DUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"

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
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
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

//...

typedef struct s_arg
{
	int	is_valid;
	t_img	img;
	t_map	map;
	t_player	player;
	t_ray	ray;
	t_game	game;
}	t_arg;


void	init_data(t_arg *arg, char *file);
int	is_file_valid(char *file);

int	get_window_size(t_arg *arg, t_map *map, int fd);
int	img_parse(t_arg *arg, t_map *map, int fd);

void	map_check(t_arg *arg, char **grid, int i, char *line);
void	texture_check(t_arg *arg, t_map *map, char *line);
void	color_check(t_arg *arg, t_map *map, char *line);
int	all_check(t_map *map);

int	map_vaild(t_arg *arg, t_map *map);

char	non_whitespace(char *str);
char	**copy_map(t_arg *arg, t_map *map, char **grid);

void	free_str(char **str);

void	exit_msg(t_arg *arg, char *msg);

#endif