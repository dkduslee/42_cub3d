/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylee <aylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 12:14:17 by aylee             #+#    #+#             */
/*   Updated: 2026/05/10 11:18:53 by aylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->screen.addr + y * game->screen.line_length
		+ x * (game->screen.bits_per_pixel / 8);
	*(int *)dst = color;
}

void	draw_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game, x, y, game->map.ceil_color);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_game *game)
{
	int	x;
	int	y;

	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(game, x, y, game->map.floor_color);
			x++;
		}
		y++;
	}
}

void	draw_walls(t_game *game)
{
	t_ray	ray;
	t_draw	things;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(game, &ray, x);
		calc_step_and_sidedist(game, &ray);
		perform_dda(game, &ray);
		calc_wall_height(game, &ray, &things);
		draw_wall_column(game, &ray, x, &things);
		x++;
	}
}

void	render(t_game *game)
{
	draw_ceiling(game);
	draw_floor(game);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
}
