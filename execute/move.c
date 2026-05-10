/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylee <aylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 12:17:24 by aylee             #+#    #+#             */
/*   Updated: 2026/05/03 20:42:16 by aylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	rotate(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

static void	move_forward_back(t_game *game, double speed)
{
	t_player	*p;
	char		**g;

	p = &game->player;
	g = game->map.grid;
	if (g[(int)(p->pos_y)][(int)(p->pos_x + p->dir_x * speed)] != '1')
		p->pos_x += p->dir_x * speed;
	if (g[(int)(p->pos_y + p->dir_y * speed)][(int)(p->pos_x)] != '1')
		p->pos_y += p->dir_y * speed;
}

static void	move_strafe(t_game *game, double speed)
{
	t_player	*p;
	char		**g;
	double		right_x;
	double		right_y;

	p = &game->player;
	g = game->map.grid;
	right_x = p->dir_y;
	right_y = -(p->dir_x);
	if (g[(int)(p->pos_y)][(int)(p->pos_x + right_x * speed)] != '1')
		p->pos_x += right_x * speed;
	if (g[(int)(p->pos_y + right_y * speed)][(int)(p->pos_x)] != '1')
		p->pos_y += right_y * speed;
}

void	move_player(t_game *game, int keycode)
{
	const double	move_speed = 0.05;

	if (keycode == KEY_W)
		move_forward_back(game, move_speed);
	else if (keycode == KEY_S)
		move_forward_back(game, -move_speed);
	else if (keycode == KEY_A)
		move_strafe(game, move_speed);
	else if (keycode == KEY_D)
		move_strafe(game, -move_speed);
}

void	rotate_player(t_game *game, int keycode)
{
	const double	rot_speed = 0.04;

	if (keycode == KEY_LEFT)
		rotate(&game->player, -rot_speed);
	else if (keycode == KEY_RIGHT)
		rotate(&game->player, rot_speed);
}
