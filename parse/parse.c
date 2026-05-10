/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:10:21 by solee             #+#    #+#             */
/*   Updated: 2026/05/05 14:35:17 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	map_parse(t_map *map, char **file_dup, int count)
{
	int	i;
	int	width;

	i = count;
	width = 0;
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (-1);
	while (file_dup[i])
	{
		if (width < (int)ft_strlen(file_dup[i]))
			width = (int)ft_strlen(file_dup[i]);
		if (map_check(map->grid, i - count, file_dup[i]) == -1)
			return (-1);
		i++;
	}
	if (width < (int)ft_strlen(file_dup[i]))
		width = (int)ft_strlen(file_dup[i]);
	map->width = width;
	map->grid[i - count] = NULL;
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

int	map_func(t_arg *arg, char *line, int *count, int *map_check)
{
	*map_check = is_space(line, '1');
	if (texture_check(arg, &(arg->map), line) < 0 || color_check(arg, &(arg->map), line) < 0)
		return (-1);
	(*count)++;
	return (0);
}

void	line_func_free(int fd, char *line, char **file_dup, t_arg *arg)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	free_str(file_dup);
	free_all(arg);
	exit(0);
}

int line_func(t_arg *arg, char **file_dup, int fd)
{
	char	*line;
	int		i;
	int		count;
	int		map_check;

	i = 0;
	count = -1;
	map_check = -1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\0' && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		file_dup[i] = ft_strdup(line);
		if (!file_dup[i])
			line_func_free(fd, line, file_dup, arg);
		if (map_check != 0)
			if (map_func(arg, line, &count, &map_check) < 0)
				line_func_free(fd, line, file_dup, arg);
		free(line);
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
		exit_msg(arg, "Malloc failed", 1);
	count = line_func(arg, file_dup, fd);
	if (count == -1)
	{
		free_str(file_dup);
		exit_msg(arg, "Map unvaild", 1);
	}
	map->height = map->height - count;
	if (all_check(map) < 0 || map_parse(map, file_dup, count) < 0)
		return (free_str(file_dup), -1);
	return (free_str(file_dup), 0);
}
