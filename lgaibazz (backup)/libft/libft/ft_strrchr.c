/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:12:06 by nbordoni          #+#    #+#             */
/*   Updated: 2022/10/10 19:30:29 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*str2;

	i = 0;
	str2 = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			str2 = (char *)(str + i);
		i++;
	}
	if (str[i] == (char)c)
		str2 = (char *)(str + i);
	return (str2);
}
