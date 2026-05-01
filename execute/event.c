/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylee <aylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 12:17:21 by aylee             #+#    #+#             */
/*   Updated: 2026/04/19 00:00:00 by aylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** 키 입력 핸들러.
** 이동/회전 후 render() 를 호출해 즉시 화면을 갱신한다.
*/
int	handle_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
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

/*
** 윈도우 닫기(X 버튼) 핸들러.
*/
int	handle_window_close(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}
