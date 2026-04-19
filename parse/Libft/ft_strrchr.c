/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:17:49 by solee             #+#    #+#             */
/*   Updated: 2025/04/16 15:10:57 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*d;

	d = NULL;
	while (*s)
	{
		if (*s == (char)c)
			d = s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return ((char *)d);
}
