/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:45:06 by solee             #+#    #+#             */
/*   Updated: 2025/04/10 12:45:25 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	const char		*ptr;

	ptr = 0;
	i = 0;
	if (!(*little))
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			j++;
			if (!(little[j]))
			{
				ptr = &big[i];
				return ((char *)ptr);
			}
		}
		i++;
	}
	return (NULL);
}
