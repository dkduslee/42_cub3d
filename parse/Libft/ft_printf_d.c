/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:33:05 by solee             #+#    #+#             */
/*   Updated: 2025/05/01 11:26:52 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_len(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i = 1;
		n = n * -1;
	}
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_printf_d(int nb)
{
	char	charnb;
	int		ret;

	ret = count_len(nb);
	if (nb < 0)
	{
		if (nb == -2147483648)
		{
			write(1, "-2147483648", 11);
			return (11);
		}
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		ft_printf_d(nb / 10);
	charnb = nb % 10 + '0';
	write(1, &charnb, 1);
	return (ret);
}
