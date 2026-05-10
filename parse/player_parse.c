/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:36:55 by solee             #+#    #+#             */
/*   Updated: 2026/05/05 13:46:06 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	set_dir_plane(t_player *player, char c)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (c == 'N')
		y = -1;
	else if (c == 'S')
		y = 1;
	else if (c == 'E')
		x = 1;
	else if (c == 'W')
		x = -1;
	else
		return (-1);
	player->dir_x = x;
	player->dir_y = y;
	player->plane_x = -0.66 * y;
	player->plane_y = 0.66 * x;
	return (0);
}

int	find_player(t_arg *arg, t_player *player, char **grid)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	ret = -1;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (ft_strchr("NSEW", grid[i][j]))
			{
				player->pos_y = i;
				player->pos_x = j;
				set_dir_plane(player, grid[i][j]);
				ret++;
			}
			j++;
		}
		i++;
	}
	if (ret > 0)
		exit_msg(arg, "Only one Player is required", 0);
	return (ret);
}
