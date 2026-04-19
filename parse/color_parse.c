/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:32:10 by solee             #+#    #+#             */
/*   Updated: 2026/04/19 13:30:54 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		exit_msg(arg, "Malloc error");
	if ((ft_strncmp(tmp[0], "F", 2) != 0) && (ft_strncmp(tmp[0], "C", 2) != 0))
		return (free_str(tmp), NULL);
	*c = *(tmp[0]);
	color = ft_split(tmp[1], ',');
	free_str(tmp);
	if (!color || !color[0] || !color[1] || !color[2] || color[3])
		exit_msg(arg, "Color unvaild");
	if (ft_atoi(color[0]) > 255 || ft_atoi(color[1]) > 255 || ft_atoi(color[2]) > 255
		|| ft_atoi(color[0]) < 0 || ft_atoi(color[1]) < 0 || ft_atoi(color[2]) < 0)
		return (NULL);
	return (color);
}

void	color_check(t_arg *arg, t_map *map, char *line)
{
	char	**color;
	char	c;

	if (!line[0] && !line[1])
		return ;
	color = get_color(arg, line, &c);
	if (!color)
		return ;
	if (c == 'F')
	{
		map->floor_color = create_trgb(0, ft_atoi(color[0]),
				ft_atoi(color[1]), ft_atoi(color[2]));
	}
	if (c == 'C')
	{
		map->ceil_color = create_trgb(0, ft_atoi(color[0]),
				ft_atoi(color[1]), ft_atoi(color[2]));
	}
}
