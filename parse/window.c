/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:22:04 by solee             #+#    #+#             */
/*   Updated: 2026/04/23 14:01:58 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_window_size(t_arg *arg, t_map *map, int fd)
{
	char	*line;
	int		i;
	int		j;

	(void)arg;
	i = 0;
	map->width = -1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		j = 0;
		while (line[j] && line[j] != '\n')
			j++;
		if (j > map->width)
			map->width = j;
		free(line);
		i++;
		line = get_next_line(fd);
	}
	free(line);
	map->height = i;
	close(fd);
	return (0);
}
