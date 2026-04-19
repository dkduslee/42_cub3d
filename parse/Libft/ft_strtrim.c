/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:47:29 by solee             #+#    #+#             */
/*   Updated: 2025/04/16 12:22:56 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		first;
	int		last;
	int		i;
	int		len;
	char	*str;

	first = 0;
	last = 0;
	len = ft_strlen(s1);
	while (s1[first] && ft_strchr(set, s1[first]))
		first++;
	while (s1[len - last - 1] && ft_strchr(set, s1[len - last - 1]))
		last++;
	if (first == last && first == len)
		str = (char *)malloc(sizeof(char) * (1));
	else
		str = (char *)malloc(sizeof(char) * (len - first - last + 1));
	if (!(str))
		return (0);
	i = 0;
	while (i < first)
		i++;
	ft_strlcpy(str, &s1[i], len - first - last + 1);
	return (str);
}
