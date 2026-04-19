/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:44:49 by solee             #+#    #+#             */
/*   Updated: 2025/04/30 17:07:30 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_printf_c(unsigned char c)
{
	int	bytes;

	bytes = 0;
	if (c == '\0')
	{
		bytes = write(1, "\0", 1);
		return (bytes);
	}
	bytes = write(1, &c, 1);
	return (bytes);
}
