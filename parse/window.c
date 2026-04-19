/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:22:04 by solee             #+#    #+#             */
/*   Updated: 2026/04/14 15:39:31 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void	image_set(t_var *var, t_img *img)
// {
// 	int	img_width;
// 	int	img_height;

// 	img->img_floor = mlx_xpm_file_to_image(var->mlx,
// 			"./textures/0.xpm", &img_width, &img_height);
// 	img->img_wall = mlx_xpm_file_to_image(var->mlx,
// 			"./textures/1.xpm", &img_width, &img_height);
// 	img->img_p = mlx_xpm_file_to_image(var->mlx,
// 			"./textures/p.xpm", &img_width, &img_height);
// 	img->img_p_exit = mlx_xpm_file_to_image(var->mlx,
// 			"./textures/pe.xpm", &img_width, &img_height);
// 	img->img_exit = mlx_xpm_file_to_image(var->mlx,
// 			"./textures/e.xpm", &img_width, &img_height);
// 	img->img_apple = mlx_xpm_file_to_image(var->mlx,
// 			"./textures/c.xpm", &img_width, &img_height);
// }

// int	check_line(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '\n')
// 		{
// 			line[i] = '\0';
// 			return (1);
// 		}
// 		else if (line[i] != 'P' && line[i] != 'E' && line[i] != 'C'
// 			&& line[i] != '1' && line[i] != '0')
// 			return (-1);
// 		i++;
// 	}
// 	return (1);
// }

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
	return (0);
}
