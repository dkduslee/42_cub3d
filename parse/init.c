/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylee <aylee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:09:59 by solee             #+#    #+#             */
/*   Updated: 2026/05/03 16:15:36 by aylee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*get_extension(char *file)
{
	char	*tmp;

	tmp = file;
	while (*file)
	{
		file++;
		if (*file == '.')
		{
			tmp = file;
			if ((file + 1) != NULL)
				file++;
		}
	}
	return (tmp);
}

int	is_file_valid(char *file)
{
	char	**path;
	int		i;

	i = 0;
	path = ft_split(file, '/');
	if (!path)
		return (-1);
	while (path[i])
		i++;
	// 이거 조건문 맞아요? 맞는데 틀렸다고 체크하는 것처럼 보이긴 함.
	if ((ft_strlen(path[i - 1]) == 4)
		&& (ft_strncmp(path[i - 1], ".cub", 4) == 0))
		return (free_str(path), -1);
	free_str(path);
	if ((ft_strncmp(get_extension(file), ".cub", 4) == 0))
		return (0);
	return (-1);
}

void	init_map(t_map *map)
{
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_path = NULL;
	map->floor_color = -1;
	map->ceil_color = -1;
}

void	init_data(t_arg *arg, char *file)
{
	int	fd1;
	int	fd2;

	if (is_file_valid(file) < 0)
		exit_msg(arg, "Map is not a \".cub\" file");
	fd1 = open(file, O_RDONLY);
	fd2 = open(file, O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
		exit_msg(arg, "Map unable to open");
	init_map(&(arg->map));
	if (get_window_size(arg, &(arg->map), fd1) < 0
		|| img_parse(arg, &(arg->map), fd2) < 0)
		exit_msg(arg, "Map unvaild");
	if (map_vaild(arg, &(arg->map)) < 0)
		exit_msg(arg, "Map unvaild");
	// arg->game.map = arg->map;
    // arg->game.player = arg->player;
	// arg->ray.map_x = arg->map.width;
	// arg->ray.map_y = arg->map.height;
	// if (mlx_setting(arg, &(arg->game), &(arg->map)) < 0)
	// 	exit_msg(arg, "Mlx error");
}
