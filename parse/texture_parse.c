/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:33:09 by solee             #+#    #+#             */
/*   Updated: 2026/05/05 14:35:42 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	texture_path_check(char *path)
{
	int	fd;

	if (!path || !path[0])
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}

int	is_texture_vaild(t_arg *arg, t_map *map, char **tmp)
{
	if ((ft_strncmp(tmp[0], "NO", 3) == 0))
	{
		if (map->no_path != NULL)
			return (exit_msg(arg, "Need only one texture", 0), -1);
		map->no_path = ft_strdup(tmp[1]);
	}
	if ((ft_strncmp(tmp[0], "SO", 3) == 0))
	{
		if (map->so_path != NULL)
			return (exit_msg(arg, "Need only one texture", 0), -1);
		map->so_path = ft_strdup(tmp[1]);
	}
	if ((ft_strncmp(tmp[0], "WE", 3) == 0))
	{
		if (map->we_path != NULL)
			return (exit_msg(arg, "Need only one texture", 0), -1);
		map->we_path = ft_strdup(tmp[1]);
	}
	if ((ft_strncmp(tmp[0], "EA", 3) == 0))
	{
		if (map->ea_path != NULL)
			return (exit_msg(arg, "Need only one texture", 0), -1);
		map->ea_path = ft_strdup(tmp[1]);
	}
	return (0);
}

int	texture_check(t_arg *arg, t_map *map, char *line)
{
	char	**tmp;

	if (!line[0])
		return (0);
	tmp = ft_split(line, ' ');
	if (!tmp)
		return (exit_msg(arg, "Map unvaild", 0), -1);
	if (!tmp[1])
		return (free_str(tmp), 0);
	if ((ft_strncmp(tmp[0], "NO", 3) != 0) && (ft_strncmp(tmp[0], "SO", 3) != 0)
		&& (ft_strncmp(tmp[0], "WE", 3) != 0)
		&& (ft_strncmp(tmp[0], "EA", 3) != 0))
		return (free_str(tmp), 0);
	if (texture_path_check(tmp[1]) < 0)
	{
		free_str(tmp);
		return (exit_msg(arg, "Texture path unvaild", 0), -1);
	}
	if (is_texture_vaild(arg, map, tmp) < 0)
		return (free_str(tmp), -1);
	free_str(tmp);
	return (0);
}
