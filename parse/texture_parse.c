/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:33:09 by solee             #+#    #+#             */
/*   Updated: 2026/04/18 16:36:15 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	testure_path_check(t_arg *arg, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (!fd)
		exit_msg(arg, "Texture path unvaild");
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
	testure_path_check(arg, tmp[1]);
	if ((ft_strncmp(tmp[0], "NO", 3) == 0))
		map->no_path = ft_strdup(tmp[1]);
	if ((ft_strncmp(tmp[0], "SO", 3) == 0))
		map->so_path = ft_strdup(tmp[1]);
	if ((ft_strncmp(tmp[0], "WE", 3) == 0))
		map->we_path = ft_strdup(tmp[1]);
	if ((ft_strncmp(tmp[0], "EA", 3) == 0))
		map->ea_path = ft_strdup(tmp[1]);
	free_str(tmp);
}