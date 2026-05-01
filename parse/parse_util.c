/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:27:20 by solee             #+#    #+#             */
/*   Updated: 2026/04/23 13:40:23 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	all_check(t_map *map)
{	
	if (map->no_path != NULL && map->so_path != NULL && map->we_path != NULL
		&& map->ea_path != NULL && map->floor_color != -1
		&& map->ceil_color != -1)
		return (0);
	return (-1);
}

void	map_check(t_arg *arg, char **grid, int i, char *line)
{
	if (!line)
	{
		grid[i] = NULL;
		return ;
	}
	grid[i] = ft_strdup(line);
	if (!grid[i])
		exit_msg(arg, "Malloc error");
}
