/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:33:09 by solee             #+#    #+#             */
/*   Updated: 2026/04/23 14:27:53 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	testure_path_check(t_arg *arg, char *path)
{
	int	fd;

	if (!path || !path[0])
		exit_msg(arg, "Texture path unvaild");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit_msg(arg, "Texture path unvaild");
}

void	is_texture_vaild(t_arg *arg, t_map *map, char **tmp)
{
	if ((ft_strncmp(tmp[0], "NO", 3) == 0))
	{
		if (map->no_path != NULL)
			exit_msg(arg, "Need only one texture");
		map->no_path = ft_strdup(tmp[1]);
	}
	if ((ft_strncmp(tmp[0], "SO", 3) == 0))
	{
		if (map->so_path != NULL)
			exit_msg(arg, "Need only one texture");
		map->so_path = ft_strdup(tmp[1]);
	}
	if ((ft_strncmp(tmp[0], "WE", 3) == 0))
	{
		if (map->we_path != NULL)
			exit_msg(arg, "Need only one texture");
		map->we_path = ft_strdup(tmp[1]);
	}
	if ((ft_strncmp(tmp[0], "EA", 3) == 0))
	{
		if (map->ea_path != NULL)
			exit_msg(arg, "Need only one texture");
		map->ea_path = ft_strdup(tmp[1]);
	}
}

void	texture_check(t_arg *arg, t_map *map, char *line)
{
	char	**tmp;

	if (!line[0])
		return ;
	tmp = ft_split(line, ' ');
	if (!tmp)
		exit_msg(arg, "Map unvaild");
	if (!tmp[1])
		return ;
	if ((ft_strncmp(tmp[0], "NO", 3) != 0) && (ft_strncmp(tmp[0], "SO", 3) != 0)
		&& (ft_strncmp(tmp[0], "WE", 3) != 0)
		&& (ft_strncmp(tmp[0], "EA", 3) != 0))
		return ;
	testure_path_check(arg, tmp[1]);
	is_texture_vaild(arg, map, tmp);
	free_str(tmp);
}
