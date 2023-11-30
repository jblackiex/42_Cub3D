/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod.c                                         :+:      :+:    :+*/
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:39:58 by nbordoni          #+#    #+#             */
/*   Updated: 2022/10/14 15:40:11 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_string(char *str, char c)
{
	size_t	st;
	size_t	y;

	y = 0;
	st = 0;
	if (str[y] == c && ++st)
		y++;
	while (str[y])
	{
		if (str[y] == c && str[y - 1] == c)
			st++;
		if (str[y] == c)
			y++;
		if (str[y] != c && str[y])
			st++;
		while (str[y] != c && str[y])
			y++;
	}
	return (st + 1);
}

static char	*ft_create_string(char *str, char c)
{
	char	*k;
	int		y;

	y = 0;
	if (str[0] == c)
		y++;
	else
	{
		while (str[y] && str[y] != c)
			y++;
	}
	k = (char *) ft_calloc(y + 1, sizeof(char));
	if (!k)
		return (NULL);
	ft_strlcpy(k, str, y + 1);
	return (k);
}

static void	*ft_free(char **ptr, int i)
{
	while (i > 0)
		free (ptr[i--]);
	free(ptr);
	return (NULL);
}

char	**ft_split_mod(char *s, char c)
{
	int		y;
	int		len;
	char	**ptr;

	if (!s)
		return (NULL);
	len = ft_string(s, c);
	ptr = (char **) ft_calloc(len + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	y = -1;
	while (++y < len)
	{
		ptr[y] = ft_create_string(s, c);
		if (!ptr[y])
			return (ft_free(ptr, y));
		s = s + ft_strlen(ptr[y]);
		if (*s == c && (*(s - 1) && (*(s - 1) != c)))
			s++;
	}
	ptr[y] = 0;
	return (ptr);
}
