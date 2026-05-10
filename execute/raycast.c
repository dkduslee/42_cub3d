/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylee <aylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 00:00:00 by aylee             #+#    #+#             */
/*   Updated: 2026/05/03 21:14:07 by aylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	ray->hit = 0;
	if (ray->dir_x == 0.0)
		ray->delta_dist_x = 1e30; //실용적인 가짜 무한대. 10^30을 의미
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0.0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

void	calc_step_and_sidedist(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y)
			* ray->delta_dist_y;
	}
}

void	check_hit(t_game *game, t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
	if (ray->map_y < 0 || ray->map_y >= game->map.height
		|| ray->map_x < 0 || ray->map_x >= game->map.width)
	{
		ray->hit = 1;
	}
	if (game->map.grid[ray->map_y][ray->map_x] == '1')
		ray->hit = 1;
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		check_hit(game, ray);
	}
	if (ray->side == 0 && ray->step_x > 0)
		ray->tex_num = TEX_EA;
	else if (ray->side == 0 && ray->step_x < 0)
		ray->tex_num = TEX_WE;
	else if (ray->side == 1 && ray->step_y > 0)
		ray->tex_num = TEX_SO;
	else
		ray->tex_num = TEX_NO;
}

void	calc_wall_height(t_game *game, t_ray *ray,
			int *line_height, int *draw_start, int *draw_end)
{
	(void)game;
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	*line_height = (int)(HEIGHT / ray->perp_wall_dist);
	*draw_start = -(*line_height) / 2 + HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = (*line_height) / 2 + HEIGHT / 2;
	if (*draw_end >= HEIGHT)
		*draw_end = HEIGHT - 1;
}

void	draw_wall_column(t_game *game, t_ray *ray,
			int x, int line_height, int draw_start, int draw_end)
{
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;
	char	*tex_addr;

	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)TEX_WIDTH);
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	step = 1.0 * TEX_HEIGHT / line_height;
	tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
	tex_addr = game->tex[ray->tex_num].addr;
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = *(int *)(tex_addr
				+ tex_y * game->tex[ray->tex_num].line_length
				+ tex_x * (game->tex[ray->tex_num].bits_per_pixel / 8));
		put_pixel(game, x, y, color);
		y++;
	}
}
