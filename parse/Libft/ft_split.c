/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:03:38 by solee             #+#    #+#             */
/*   Updated: 2025/04/15 16:20:02 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	str_free(char **str, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free (str[i]);
		i++;
	}
	free (str);
}

static char	*str_dup(const char *s, int *idx, int len)
{
	int		i;
	char	*str;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = s[i + *idx];
		i++;
	}
	str[i] = '\0';
	*idx += len;
	return (str);
}

static int	count_word(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_split2(char const *s, char c, int *idx)
{
	int	len;
	int	i;

	i = 0;
	while (s[*idx] == c && s[*idx] != 0)
		(*idx)++;
	i = *idx;
	while (!(s[i] == c) && s[i] != 0)
		i++;
	len = i - *idx;
	return (str_dup(s, idx, len));
}

char	**ft_split(char const *s, char c)
{
	int			i;
	int			idx;
	int			words;
	char		**str;

	i = 0;
	idx = 0;
	if (s == 0 || *s == '\0')
		return (0);
	words = count_word(s, c);
	str = (char **)malloc(sizeof(char *) * (words + 1));
	if (!str)
		return (0);
	while (i < words)
	{
		str[i] = ft_split2(s, c, &idx);
		if (!(str[i]))
		{
			str_free(str, i);
			return (0);
		}
		i++;
	}
	str[i] = 0;
	return (str);
}
