/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:34:34 by solee             #+#    #+#             */
/*   Updated: 2025/04/16 11:10:34 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	s_len;
	char			*ptr;

	ptr = 0;
	s_len = ft_strlen(s);
	if (start > s_len)
		return (NULL);
	else if (len + start > s_len)
		ptr = (char *)malloc(sizeof(char) * (s_len - start + 1));
	else
		ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!(ptr))
		return (NULL);
	i = 0;
	while (i < len && i + start < s_len)
	{
		ptr[i] = s[i + start];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
