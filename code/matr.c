/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:43:33 by nbordoni          #+#    #+#             */
/*   Updated: 2023/02/12 15:43:35 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Cub3d.h"

void	ft_free_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	**get_map(char *mapy)
{
	char	**result;
	char	*holder;
	char	*old_address;
	char	*map;
	int		fd;

	fd = open(mapy, O_RDONLY);
	if (fd == -1)
		print_error(fd, NULL);
	map = ft_strdup("");
	while (1)
	{
		holder = get_next_line(fd);
		if (!holder)
			break ;
		old_address = map;
		map = ft_strjoin(old_address, holder);
		ft_free_ptr((void *)&old_address);
		ft_free_ptr((void *)&holder);
	}

	result = ft_split_mod(map, '\n');
	ft_free_ptr((void *)&map);
	return (close(fd), result);
}
