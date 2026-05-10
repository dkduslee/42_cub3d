/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:57:56 by solee             #+#    #+#             */
/*   Updated: 2026/05/05 13:44:52 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	dfs(t_arg *arg, char **grid, int y, int x)
{
	if (y < 0 || y >= arg->map.height || x < 0)
	{
		arg->is_valid = 0;
		return ;
	}
	if (!grid[y] || x >= (int)ft_strlen(grid[y]) || grid[y][x] == ' ')
	{
		arg->is_valid = 0;
		return ;
	}
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return ;
	grid[y][x] = 'V';
	dfs(arg, grid, y - 1, x);
	dfs(arg, grid, y + 1, x);
	dfs(arg, grid, y, x - 1);
	dfs(arg, grid, y, x + 1);
}

int	is_walls_valid(t_arg *arg, char **grid)
{
	arg->is_valid = 1;
	dfs(arg, grid, (int)arg->player.pos_y, (int)arg->player.pos_x);
	return (arg->is_valid);
}

int	find_map_invaild_c(char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (!ft_strchr("10NSEW ", grid[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	map_vaild(t_arg *arg, t_map *map)
{
	char	**temp_map;

	if (find_player(arg, &(arg->player), map->grid) < 0)
		exit_msg(arg, "Player is required", 0);
	if (find_map_invaild_c(map->grid) < 0)
		exit_msg(arg, "Map allowed charactors are '1', '0', \"NSEW\" ", 0);
	temp_map = copy_map(arg, map, map->grid);
	if (!is_walls_valid(arg, temp_map))
	{
		free_str(temp_map);
		exit_msg(arg, "Map not closed", 0);
	}
	free_str(temp_map);
	return (0);
}
