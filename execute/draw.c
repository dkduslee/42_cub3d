/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylee <aylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 10:42:15 by aylee             #+#    #+#             */
/*   Updated: 2026/05/10 12:59:10 by aylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	calc_wall_height(t_game *game, t_ray *ray,
			t_draw *things)
{
	(void)game;
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
    if (ray->perp_wall_dist < 0.003)
    {
        ray->perp_wall_dist = 0.003;
    }
	things->height = (int)(HEIGHT / ray->perp_wall_dist);
	things->start = -things->height / 2 + HEIGHT / 2;
	if (things->start < 0)
		things->start = 0;
	things->end = things->height / 2 + HEIGHT / 2;
	if (things->end >= HEIGHT)
		things->end = HEIGHT - 1;
}

static void	cal_tex(t_game *game, t_ray *ray, t_draw *things)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	things->tex_x = (int)(wall_x * (double)TEX_WIDTH);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
		things->tex_x = TEX_WIDTH - things->tex_x - 1;
}

void	draw_wall_column(t_game *game, t_ray *ray, int x, t_draw *things)
{
	int		y;
	int		tex_y;
	int		color;
	t_img	*img;

	cal_tex(game, ray, things);
	things->step = 1.0 * TEX_HEIGHT / things->height;
	things->tex_pos = (things->start
			- HEIGHT / 2 + things->height / 2) * things->step;
	img = &game->tex[ray->tex_num];
	y = things->start;
	while (y < things->end)
	{
		tex_y = (int)things->tex_pos & (TEX_HEIGHT - 1);
		things->tex_pos += things->step;
		color = *(int *)(img->addr + tex_y * img->line_length
				+ things->tex_x * (img->bits_per_pixel / 8));
		put_pixel(game, x, y, color);
		y++;
	}
}
