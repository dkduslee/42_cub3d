/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:41:09 by solee             #+#    #+#             */
/*   Updated: 2025/04/16 12:00:00 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;

	if (size != 0 && nmemb > ((size_t) -1) / size)
		return (NULL);
	str = malloc (nmemb * size);
	if (!str)
		return (NULL);
	ft_memset(str, 0, (nmemb * size));
	return (str);
}
