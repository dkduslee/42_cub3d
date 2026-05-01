/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:19:33 by solee             #+#    #+#             */
/*   Updated: 2026/05/01 17:03:33 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    image_set(t_game *game, t_map *map)
{
    int w;
    int h;

    game->tex[0].img = mlx_xpm_file_to_image(game->mlx, map->no_path, &w, &h);
    game->tex[1].img = mlx_xpm_file_to_image(game->mlx, map->so_path, &w, &h);
    game->tex[2].img = mlx_xpm_file_to_image(game->mlx, map->we_path, &w, &h);
    game->tex[3].img = mlx_xpm_file_to_image(game->mlx, map->ea_path, &w, &h);
    if (!game->tex[0].img || !game->tex[1].img || !game->tex[2].img || !game->tex[3].img)
        exit_msg(NULL, "Texture file open failed");
    game->tex[0].addr = mlx_get_data_addr(game->tex[0].img, &game->tex[0].bits_per_pixel, &game->tex[0].line_length, &game->tex[0].endian);
    game->tex[1].addr = mlx_get_data_addr(game->tex[1].img, &game->tex[1].bits_per_pixel, &game->tex[1].line_length, &game->tex[1].endian);
    game->tex[2].addr = mlx_get_data_addr(game->tex[2].img, &game->tex[2].bits_per_pixel, &game->tex[2].line_length, &game->tex[2].endian);
    game->tex[3].addr = mlx_get_data_addr(game->tex[3].img, &game->tex[3].bits_per_pixel, &game->tex[3].line_length, &game->tex[3].endian);
}

int	window_close(t_arg *arg)
{
	(void)arg;
	// free_everything(arg);
	exit(0);
	return (0);
}

int	mlx_setting(t_arg *arg, t_game *game, t_map *map)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (-1);
	image_set(game, map);
	game->win = mlx_new_window(game->mlx,
			WIDTH, HEIGHT, "cub3D");
	game->screen.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bits_per_pixel,
			&game->screen.line_length,
			&game->screen.endian);
	mlx_hook(game->win, 17, 0, window_close, arg);
	return (0);
}
