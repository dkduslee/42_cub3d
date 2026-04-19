/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:59:06 by solee             #+#    #+#             */
/*   Updated: 2026/04/15 13:00:14 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	non_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'
			|| str[i] == '\n'))
		i++;
	return (str[i]);
}

char	**copy_map(t_arg *arg, t_map *map, char **grid)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(sizeof(char *) * (map->height + 1), 0);
	if (!tmp)
		exit_msg(arg, "Malloc error");
	while (i < map->height)
	{
		tmp[i] = ft_strdup(grid[i]);
		if (!tmp[i])
			exit_msg(arg, "Malloc error");
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}
