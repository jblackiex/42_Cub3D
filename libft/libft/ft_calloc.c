/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:15:41 by nbordoni          #+#    #+#             */
/*   Updated: 2022/10/10 19:06:17 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*src;

	src = (void *)malloc(nmemb * size);
	if (!src)
		return (NULL);
	ft_bzero(src, nmemb);
	return (src);
}
