/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:48:30 by solee             #+#    #+#             */
/*   Updated: 2026/04/13 15:33:02 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	j;
	int	ret;

	j = 1;
	ret = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
	{
		j = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		if ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
			nptr++;
		if (*nptr >= '0' && *nptr <= '9')
			ret = ret * 10 + *nptr - 48;
		nptr++;
	}
	return (ret * j);
}
