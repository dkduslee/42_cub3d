/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:26:23 by solee             #+#    #+#             */
/*   Updated: 2025/04/16 14:02:21 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup_str;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	dup_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!(dup_str))
		return (NULL);
	while (s[i] != '\0')
	{
		dup_str[i] = s[i];
		i++;
	}
	dup_str[i] = '\0';
	return (dup_str);
}
