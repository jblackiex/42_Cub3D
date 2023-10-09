/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:52:50 by nbordoni          #+#    #+#             */
/*   Updated: 2022/10/10 19:04:34 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t		i;
	size_t		n;
	char		*dest;

	i = ((ft_strlen(s1)) + (ft_strlen(s2)));
	dest = malloc((i + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < (ft_strlen(s1)))
	{
		dest[i] = s1[i];
		i++;
	}
	n = 0;
	while (n < ft_strlen(s2))
	{
		dest[i] = s2[n];
		i++;
		n++;
	}
	dest[i] = '\0';
	return (dest);
}
