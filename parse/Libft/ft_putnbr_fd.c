/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:38:05 by solee             #+#    #+#             */
/*   Updated: 2025/04/10 11:59:52 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	nb;

	if (n < 0)
	{
		write(fd, "-", 1);
		if (n == -2147483648)
		{
			write(fd, "2147483648", 10);
			return ;
		}
		n = n * -1;
	}
	if (n / 10 == 0)
	{
		n = n % 10;
		nb = n + 48;
		write(fd, &nb, 1);
		return ;
	}
	nb = n % 10 + 48;
	n = n / 10;
	ft_putnbr_fd(n, fd);
	write(fd, &nb, 1);
}
