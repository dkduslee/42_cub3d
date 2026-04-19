/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:10:21 by solee             #+#    #+#             */
/*   Updated: 2026/04/19 13:30:34 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	map_parse(t_arg *arg, t_map *map, char **file_dup, int count)
{
	int	i;

	i = count;
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (-1);
	while (file_dup[i])
	{
		map_check(arg, map->grid, i - count, file_dup[i]);
		i++;
	}
	map->grid[i - count] = '\0';
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

void	map_func(t_arg *arg, char *line, int *count, int *map_check)
{
	*map_check = is_space(line, '1');
	texture_check(arg, &(arg->map), line);
	color_check(arg, &(arg->map), line);
	// if (is_space(line, "NO") < 0 || is_space(line, "no") < 0
	// 	|| is_space(line, "no") < 0 || is_space(line, "no") < 0 || )
	(*count)++;
}

int	line_func(t_arg *arg, char **file_dup, int fd)
{
	char	*line;
	int		i;
	int		count;
	int		map_check;

	i = 0;
	count = -1;
	map_check = -1;
	line = get_next_line(fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		file_dup[i] = ft_strdup(line);
		if (!file_dup[i])
			exit_msg(arg, "Malloc failed");
		if (map_check != 0)
			map_func(arg, line, &count, &map_check);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (count);
}

int	img_parse(t_arg *arg, t_map *map, int fd)
{
	char	**file_dup;
	int		count;

	file_dup = ft_calloc(map->height + 1, sizeof(char *));
	if (!file_dup)
		exit_msg(arg, "Malloc failed");
	count = line_func(arg, file_dup, fd);
	if (count == -1)
		exit_msg(arg, "Map unvaild");
	map->height = map->height - count;
	if (all_check(map) < 0 || map_parse(arg, map, file_dup, count) < 0)
		return (free_str(file_dup), -1);
	return (free_str(file_dup), 0);
}
