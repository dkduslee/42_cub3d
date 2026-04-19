/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:37:12 by solee             #+#    #+#             */
/*   Updated: 2026/04/07 15:15:35 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_printf_u(unsigned int nb)
{
	char	charnb;
	int		ret;

	ret = count_len(nb);
	if (nb >= 10)
		ft_printf_u(nb / 10);
	charnb = nb % 10 + '0';
	write(1, &charnb, 1);
	return (ret);
}
