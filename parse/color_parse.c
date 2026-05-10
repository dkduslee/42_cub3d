/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:32:10 by solee             #+#    #+#             */
/*   Updated: 2026/05/05 14:40:58 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

char	**get_color(t_arg *arg, char *line, char *c)
{
	char	**tmp;
	char	**color;

	tmp = ft_split(line, ' ');
	if (!tmp)
		return (exit_msg(arg, "Malloc error", 0), NULL);
	if ((ft_strncmp(tmp[0], "F", 2) != 0) && (ft_strncmp(tmp[0], "C", 2) != 0))
		return (free_str(tmp), NULL);
	*c = *(tmp[0]);
	color = ft_split(tmp[1], ',');
	free_str(tmp);
	if (!color)
		return (exit_msg(arg, "Color unvaild", 0), NULL);
	if (!color[0] || !color[1] || !color[2] || color[3])
	{
		free_str(color);
		return (exit_msg(arg, "Color unvaild", 0), NULL);
	}
	if (ft_atoi(color[0]) > 255 || ft_atoi(color[1]) > 255
		|| ft_atoi(color[2]) > 255 || ft_atoi(color[0]) < 0
		|| ft_atoi(color[1]) < 0 || ft_atoi(color[2]) < 0)
		return (exit_msg(arg, "Color unvaild", 0), free_str(color), NULL);
	return (color);
}

int	color_check(t_arg *arg, t_map *map, char *line)
{
	char	**color;
	char	c;

	if (!line[0] || !line[1])
		return (0);
	if ((ft_strncmp(line, "F", 1) != 0) && (ft_strncmp(line, "C", 1) != 0))
		return (0);
	color = get_color(arg, line, &c);
	if (!color)
		return (-1);
	if (c == 'F')
	{
		if (map->floor_color != -1)
			return (exit_msg(arg, "Need only one floor color", 0), free_str(color), -1);
		map->floor_color = create_trgb(0, ft_atoi(color[0]),
				ft_atoi(color[1]), ft_atoi(color[2]));
	}
	if (c == 'C')
	{
		if (map->ceil_color != -1)
			return (exit_msg(arg, "Need only one ceiling color", 0), free_str(color), -1);
		map->ceil_color = create_trgb(0, ft_atoi(color[0]),
				ft_atoi(color[1]), ft_atoi(color[2]));
	}
	free_str(color);
	return (0);
}
