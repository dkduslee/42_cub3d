/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:51:17 by solee             #+#    #+#             */
/*   Updated: 2026/05/01 17:05:03 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_arg	arg;

	ft_memset(&arg, 0, sizeof(t_arg));
	if (ac != 2 || !av[1])
		exit_msg(&arg, "Need one map file");
	init_data(&arg, av[1]);
	arg.game.map = arg.map;
    arg.game.player = arg.player;
	arg.ray.map_x = arg.map.width;
	arg.ray.map_y = arg.map.height;
	if (mlx_setting(&arg, &(arg.game), &(arg.map)) < 0)
		exit_msg(&arg, "Mlx error");
	render(&(arg.game));
	mlx_loop(arg.game.mlx);
	return (0);
}