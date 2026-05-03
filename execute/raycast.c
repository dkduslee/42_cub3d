/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylee <aylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 00:00:00 by aylee             #+#    #+#             */
/*   Updated: 2026/05/03 20:31:59 by aylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/*
** 화면 열 x 에 해당하는 광선의 방향과 맵 초기 위치를 설정한다.
** camera_x : -1(왼쪽 끝) ~ +1(오른쪽 끝)
** ray.dir   : dir + camera_x * plane  (벡터 합산)
*/
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

/*
** 광선이 이동할 방향(step)과
** 현재 위치에서 첫 번째 격자선까지의 거리(side_dist)를 초기화한다.
*/
void	calc_step_and_sidedist(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0) //왼쪽으로 가는 광선
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - ray->map_x)
			* ray->delta_dist_x; //실제 광선 길이 단위로 변환.
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

/*
** DDA(Digital Differential Analysis) 루프:
** 가까운 격자선 방향으로 한 칸씩 전진하며 벽을 탐색한다.
** side == 0 : x축 방향 벽(N/S), side == 1 : y축 방향 벽(E/W)
** 텍스처 번호는 충돌 면과 광선 방향으로 결정한다.
*/
void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x; //다음 x축 격자선까지의 거리로 갱신
			ray->map_x += ray->step_x; //격자 한 칸 이동
			ray->side = 0; //x축 방향 벽 충돌
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
			ray->hit = 1; //맵 밖으로 나가면 충돌 처리
			break ;
		}
		if (game->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
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

/*
** 카메라 평면까지의 수직 거리(perp_wall_dist)로 벽 높이를 계산한다.
** perp_wall_dist 를 쓰는 이유: 단순 유클리드 거리를 쓰면 어안(fisheye)
** 왜곡이 생기기 때문에 카메라 평면에 수직인 성분만 취한다.
**
** 도출:
**   실제 벽 높이 = 1 (격자 1칸 = 1)
**   카메라 거리  = 1 (정규화)
**   닮음삼각형: 1/perp = lineHeight/HEIGHT
**   => lineHeight = HEIGHT / perp_wall_dist
**
** drawStart/End: 화면 중앙(HEIGHT/2)을 기준으로 위아래 절반씩 배치
*/
void	calc_wall_height(t_game *game, t_ray *ray,
			int *line_height, int *draw_start, int *draw_end)
{
	(void)game;
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos_x
				+ (1 - ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos_y
				+ (1 - ray->step_y) / 2.0) / ray->dir_y;
	*line_height = (int)(HEIGHT / ray->perp_wall_dist);
	*draw_start = -(*line_height) / 2 + HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = (*line_height) / 2 + HEIGHT / 2;
	if (*draw_end >= HEIGHT)
		*draw_end = HEIGHT - 1;
}

/*
** 텍스처에서 해당 열(x)의 픽셀을 샘플링해 화면 버퍼에 기록한다.
**
** wall_x : 벽면에서 광선이 닿은 위치 (0.0 ~ 1.0)
**   => 텍스처의 가로 좌표(tex_x)를 결정
**
** step    : 화면 픽셀 1개당 텍스처를 몇 픽셀 건너뛸지
**   => 가까운 벽은 step이 작아 텍스처가 크게 보임
**
** tex_x 반전: 광선 방향에 따라 텍스처가 좌우 뒤집혀 보이는 것을 보정
**
** 음영 없음: side 구분 없이 텍스처 원색 그대로 출력
*/
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
