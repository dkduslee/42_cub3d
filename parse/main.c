/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:51:17 by solee             #+#    #+#             */
/*   Updated: 2026/04/10 15:23:57 by solee            ###   ########.fr       */
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
//	parse_arg(arg);
	//그리기
//	free_all(arg);
	return (0);
}