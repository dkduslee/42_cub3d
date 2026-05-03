/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylee <aylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 12:17:24 by aylee             #+#    #+#             */
/*   Updated: 2026/05/03 19:31:07 by aylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// angle > 0 : 반시계(왼쪽), angle < 0 : 시계(오른쪽)
// 이 부분이 좀 달라서 확인 해야할 듯.
static void rotate(t_player *p, double angle)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

/*
** W/S 이동: dir 방향으로 move_speed 만큼 전후진.
** x/y 충돌을 독립적으로 확인해 벽을 따라 슬라이드할 수 있게 한다.
** grid[y][x] 순서임에 주의 (행이 y, 열이 x).
*/
static void move_forward_back(t_game *game, double speed)
{
	t_player *p;
	char **g;

	p = &game->player;
	g = game->map.grid;
	if (g[(int)(p->pos_y)][(int)(p->pos_x + p->dir_x * speed)] != '1')
		p->pos_x += p->dir_x * speed;
	if (g[(int)(p->pos_y + p->dir_y * speed)][(int)(p->pos_x)] != '1')
		p->pos_y += p->dir_y * speed;
}

/*
** W/S/A/D 키 입력 처리.
*/
static void move_strafe(t_game *game, double speed)
{
	t_player *p;
	char **g;
	double right_x;
	double right_y;

	printf("grid ptr: %p\n", game->map.grid);
	printf("grid[0]: %s\n", game->map.grid[0]);
	//여기서 문제 확인

	
	p = &game->player;
	g = game->map.grid;
	right_x = p->dir_y; // dir을 -90도 회전: (dir_y, -dir_x) = 오른쪽
	right_y = -(p->dir_x);
	if (g[(int)(p->pos_y)][(int)(p->pos_x + right_x * speed)] != '1')
		p->pos_x += right_x * speed;
	if (g[(int)(p->pos_y + right_y * speed)][(int)(p->pos_x)] != '1')
		p->pos_y += right_y * speed;
}

void move_player(t_game *game, int keycode)
{
	const double move_speed = 0.05;

	if (keycode == KEY_W)
		move_forward_back(game, move_speed);
	else if (keycode == KEY_S)
		move_forward_back(game, -move_speed);
	else if (keycode == KEY_A)
		move_strafe(game, move_speed); // 왼쪽
	else if (keycode == KEY_D)
		move_strafe(game, -move_speed); // 오른쪽
}

/*
** 좌우 화살표 키 처리 (A/D 와 동일한 회전).
*/
void rotate_player(t_game *game, int keycode)
{
	const double rot_speed = 0.04;

	if (keycode == KEY_LEFT)
		rotate(&game->player, -rot_speed);
	else if (keycode == KEY_RIGHT)
		rotate(&game->player, rot_speed);
}
