/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:16:37 by solee             #+#    #+#             */
/*   Updated: 2025/04/16 15:10:36 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*d;

	d = NULL;
	if (!s)
		return ((char *)d);
	while (*s)
	{
		if (*s == (char)c)
		{
			d = s;
			return ((char *)d);
		}
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return ((char *)d);
}
