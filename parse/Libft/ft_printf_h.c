/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_h.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:10:23 by solee             #+#    #+#             */
/*   Updated: 2025/05/01 11:27:32 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_len(size_t nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		len++;
		nb /= 16;
	}
	return (len);
}

static void	write_h(unsigned int integ, const char check)
{
	if (integ >= 16)
		write_h(integ / 16, check);
	if (check == 'x')
		write(1, &"0123456789abcdef"[integ % 16], 1);
	else
		write(1, &"0123456789ABCDEF"[integ % 16], 1);
	return ;
}

int	ft_printf_h(unsigned int temp, const char check)
{
	int		bytes;

	bytes = 0;
	write_h(temp, check);
	bytes += count_len(temp);
	return (bytes);
}
