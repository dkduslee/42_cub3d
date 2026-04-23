/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylee <aylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 12:14:17 by aylee             #+#    #+#             */
/*   Updated: 2026/04/19 00:00:00 by aylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** 화면 버퍼의 (x, y) 위치에 color 를 기록한다.
** mlx 이미지 addr 은 1차원 배열이므로
** 오프셋 = y * line_length + x * (bpp / 8)
*/
void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->screen.addr
		+ y * game->screen.line_length
		+ x * (game->screen.bits_per_pixel / 8);
	*(int *)dst = color;
}

/*
** 천장을 화면 위 절반에 단색으로 채운다.
*/
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

/*
** 바닥을 화면 아래 절반에 단색으로 채운다.
*/
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

/*
** 화면의 모든 열(x = 0 ~ WIDTH-1)에 대해:
**   1. 광선 초기화 (init_ray)
**   2. DDA 초기값 설정 (calc_step_and_sidedist)
**   3. DDA 루프로 벽 탐색 (perform_dda)
**   4. 벽 높이 계산 (calc_wall_height)
**   5. 텍스처 열 그리기 (draw_wall_column)
*/
void	draw_walls(t_game *game)
{
	t_ray	ray;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(game, &ray, x);
		calc_step_and_sidedist(game, &ray);
		perform_dda(game, &ray);
		calc_wall_height(game, &ray, &line_height, &draw_start, &draw_end);
		draw_wall_column(game, &ray, x, line_height, draw_start, draw_end);
		x++;
	}
}

/*
** 매 프레임 렌더링 진입점:
**   천장 -> 바닥 -> 벽 순으로 그린 뒤
**   화면 버퍼를 윈도우에 출력한다.
*/
void	render(t_game *game)
{
	draw_ceiling(game);
	draw_floor(game);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
}
