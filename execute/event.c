/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylee <aylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 12:17:21 by aylee             #+#    #+#             */
/*   Updated: 2026/05/10 13:07:40 by aylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	handle_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		free_all_exe(game);
		exit(0);
	}
	if (keycode == KEY_W || keycode == KEY_S
		|| keycode == KEY_A || keycode == KEY_D)
		move_player(game, keycode);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		rotate_player(game, keycode);
	render(game);
	return (0);
}

int	handle_window_close(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}
