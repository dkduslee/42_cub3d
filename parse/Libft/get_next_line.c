/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:55:17 by solee             #+#    #+#             */
/*   Updated: 2025/05/23 15:59:31 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	free_chars(char *buf, char *line, char **save_extra)
{
	free (buf);
	if (!line && *save_extra)
	{
		free(*save_extra);
		*save_extra = NULL;
	}
}

char	*get_next_line_main(char **save_extra)
{
	char	*newline;
	char	*temp;
	char	*line;
	int		len;

	if (!*save_extra || **save_extra == '\0')
		return (NULL);
	newline = ft_strchr(*save_extra, '\n');
	len = newline - *save_extra + 1;
	if (newline)
	{
		line = ft_substr(*save_extra, 0, len);
		temp = ft_substr(*save_extra, len, ft_strlen(*save_extra));
		free (*save_extra);
		*save_extra = temp;
	}
	else
	{
		line = ft_substr(*save_extra, 0, ft_strlen(*save_extra));
		free (*save_extra);
		*save_extra = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*save_extra;
	char		*save;
	char		*line;
	char		*buf;
	int			bytes;

	save = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (!ft_strchr(save, '\n'))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buf[bytes] = '\0';
		save = ft_strjoin(save_extra, buf);
		free (save_extra);
		save_extra = save;
	}
	line = get_next_line_main(&save_extra);
	free_chars(buf, line, &save_extra);
	return (line);
}
