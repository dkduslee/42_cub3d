/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:35:08 by solee             #+#    #+#             */
/*   Updated: 2025/05/01 13:23:01 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_len(size_t nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb /= 16;
	}
	return (len);
}

static void	write_p(unsigned long integ)
{
	if (integ == 0)
		return ;
	write_p(integ / 16);
	write(1, &"0123456789abcdef"[integ % 16], 1);
	return ;
}

int	ft_printf_p(unsigned long temp)
{
	int					bytes;

	bytes = 0;
	if (temp == 0)
	{	
		bytes += write(1, "(nil)", 5);
		return (bytes);
	}
	bytes += write(1, "0x", 2);
	write_p(temp);
	bytes += count_len(temp);
	return (bytes);
}
