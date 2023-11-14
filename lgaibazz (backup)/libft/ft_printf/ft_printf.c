/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:10:55 by nbordoni          #+#    #+#             */
/*   Updated: 2023/02/12 15:10:58 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

int	ft_core(char c, va_list args)
{
	int	count;

	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_print_s((va_arg(args, char *))));
	else if (c == 'i' || c == 'd')
		return (ft_putnbr((va_arg(args, int))));
	else if (c == 'u')
		return (ft_putnbr_baseu((va_arg(args, unsigned int))));
	else if (c == 'x')
		return (ft_putnbr_basex((va_arg(args, unsigned int)), 1));
	else if (c == 'X')
		return (ft_putnbr_basex((va_arg(args, unsigned int)), 0));
	else if (c == '%')
		return (ft_putchar(c));
	else
	{
		count = ft_putchar('%');
		return (count + ft_putchar(c));
	}
}

int	perc_check(const char *str, va_list args)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			count += ft_core(*str, args);
		}
		else
			count += ft_putchar(*str);
		str++;
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, str);
	if (!str)
		return (0);
	count = perc_check(str, args);
	va_end(args);
	return (count);
}
