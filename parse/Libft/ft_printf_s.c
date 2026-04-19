/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:35:51 by solee             #+#    #+#             */
/*   Updated: 2025/05/02 15:57:17 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_printf_s(const char *s)
{
	int	bytes;

	bytes = 0;
	if (s == NULL)
	{
		bytes += write(1, "(null)", 6);
		return (bytes);
	}
	while (*s)
	{
		bytes += write(1, s, 1);
		s++;
	}
	return (bytes);
}
