/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:42:50 by nbordoni          #+#    #+#             */
/*   Updated: 2023/02/12 15:42:53 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Cub3d.h"

static void	ft_find(char **temp, t_vector size, t_vector pos)
{
	if (!temp[pos.y][pos.x])
		size.flag = 1;
	if (size.flag || pos.x < 0 || pos.x > size.x || pos.y < 0
		|| pos.y >= size.y
		|| temp[pos.y][pos.x] == '1')
		return ;
	if (temp[pos.y][pos.x] == ' ')
		size.flag = 1;
	temp[pos.y][pos.x] = '1';
	size.count++;
	ft_find(temp, size, (t_vector){pos.x + 1, pos.y});
	ft_find(temp, size, (t_vector){pos.x - 1, pos.y});
	ft_find(temp, size, (t_vector){pos.x, pos.y + 1});
	ft_find(temp, size, (t_vector){pos.x, pos.y - 1});
}

int	ft_flood_fill(char **tab, t_vector size, t_vector begin)
{
	int	y;
	int	x;

	y = 1;
	size.flag = 0;
	ft_find(tab, size, begin);
	if (size.flag) //|| tab[y][0] != 'L' || tab[y][size.x + 1] != 'L'
		return (1);
	while (tab[y])
	{
		if (!y || y == size.y + 1)
		{
			x = 0;
			while (tab[y][x])
				if (tab[y][x++] != 'L')
					return (1);
		}
		if (tab[y][0] != 'L' || tab[y][size.x + 1] != 'L')
			return (1);
		y++;
	}
	return (0);
}
