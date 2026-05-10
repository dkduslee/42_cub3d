/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:27:20 by solee             #+#    #+#             */
/*   Updated: 2026/05/10 13:45:41 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	all_check(t_map *map)
{	
	if (map->no_path != NULL && map->so_path != NULL && map->we_path != NULL
		&& map->ea_path != NULL && map->floor_color != -1
		&& map->ceil_color != -1)
		return (0);
	return (-1);
}

int	map_check(char **grid, int i, char *line)
{
	if (!line)
	{
		grid[i] = NULL;
		return (-1);
	}
	grid[i] = ft_strdup(line);
	if (!grid[i])
		return (-1);
	return (0);
}

int	is_space(char *file_dup, char c)
{
	int	i;

	i = 0;
	while (file_dup[i] && (file_dup[i] == ' '
			|| file_dup[i] == '\t' || file_dup[i] == '\n'))
		i++;
	if (file_dup[i] && file_dup[i] == c)
		return (0);
	return (-1);
}
