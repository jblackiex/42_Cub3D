/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:11:10 by nbordoni          #+#    #+#             */
/*   Updated: 2023/02/12 15:11:13 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
	if (i == 0)
		return (0);
	return (i);
}

int	ft_print_s(char *c)
{
	if (!c)
	{
		return (ft_putstr("(null)"));
	}
	else
	{
		return (ft_putstr(c));
	}
}
