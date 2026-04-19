/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee <solee@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:04:13 by solee             #+#    #+#             */
/*   Updated: 2025/07/03 12:01:20 by solee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	write_printf(va_list args, const char *fmt, int i)
{
	int	bytes;

	bytes = 0;
	if (fmt[i + 1] == 'c')
		bytes += ft_printf_c((unsigned char)va_arg(args, int));
	else if (fmt[i + 1] == 's')
		bytes += ft_printf_s((const char *)va_arg(args, char *));
	else if (fmt[i + 1] == 'p')
		bytes += ft_printf_p((unsigned long)va_arg(args, void *));
	else if (fmt[i + 1] == 'd')
		bytes += ft_printf_d(va_arg(args, int));
	else if (fmt[i + 1] == 'i')
		bytes += ft_printf_d(va_arg(args, int));
	else if (fmt[i + 1] == 'u')
		bytes += ft_printf_u(va_arg(args, unsigned int));
	else if (fmt[i + 1] == 'x')
		bytes += ft_printf_h(va_arg(args, unsigned int), 'x');
	else if (fmt[i + 1] == 'X')
		bytes += ft_printf_h(va_arg(args, unsigned int), 'X');
	else if (fmt[i + 1] == '%')
		bytes += ft_printf_c(fmt[i + 1]);
	return (bytes);
}

int	ft_printf(const char *fmt, ...)
{
	int		i;
	int		ret;
	va_list	args;

	if (!fmt)
		return (-1);
	va_start(args, fmt);
	i = 0;
	ret = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			ret += write_printf(args, fmt, i);
			i++;
		}
		else
			ret += write(1, &fmt[i], 1);
		i++;
	}
	va_end(args);
	return (ret);
}
