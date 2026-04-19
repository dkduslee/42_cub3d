/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:28:53 by solee             #+#    #+#             */
/*   Updated: 2026/04/13 15:34:00 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_len(int n)
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

char	*ft_itoa(int n)
{
	int		i;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = str_len(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!(str))
		return (0);
	str[i] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	i--;
	while (i >= 0)
	{
		if (str[i] == '-')
			break ;
		str[i] = n % 10 + 48;
		n = n / 10;
		i--;
	}
	return (str);
}
