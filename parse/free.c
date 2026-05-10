/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:37:42 by solee             #+#    #+#             */
/*   Updated: 2026/05/05 14:17:22 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_mlx(t_game *game)
{
	int	i;

	if (game->mlx)
	{
		i = 0;
		while (i < 4)
		{
			if (game->tex[i].img)
				mlx_destroy_image(game->mlx, game->tex[i].img);
			i++;
		}
		if (game->screen.img)
			mlx_destroy_image(game->mlx, game->screen.img);
		if (game->win)
		{
			mlx_clear_window(game->mlx, game->win);
			mlx_destroy_window(game->mlx, game->win);
		}
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	free_all(t_arg *arg)
{
	free_mlx(&(arg->game));
	if (arg->map.no_path)
		free(arg->map.no_path);
	if (arg->map.so_path)
		free(arg->map.so_path);
	if (arg->map.we_path)
		free(arg->map.we_path);
	if (arg->map.ea_path)
		free(arg->map.ea_path);
	if (arg->map.grid)
		free_str(arg->map.grid);
}

void	free_all_exe(t_game *game)
{
	free_mlx(game);
	if (game->map.no_path)
		free(game->map.no_path);
	if (game->map.so_path)
		free(game->map.so_path);
	if (game->map.we_path)
		free(game->map.we_path);
	if (game->map.ea_path)
		free(game->map.ea_path);
	if (game->map.grid)
		free_str(game->map.grid);
}
