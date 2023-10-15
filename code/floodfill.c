/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill->c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42->fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:42:50 by nbordoni          #+#    #+#             */
/*   Updated: 2023/02/12 15:42:53 by nbordoni         ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Cub3d.h"

static void	ft_find(char **temp, t_vector *size, t_vector pos)
{
	if (size->flag || !(&temp[pos.y][pos.x]) || temp[pos.y][pos.x] == ' ' || 
		temp[pos.y][pos.x] == '\t')
	{
		size->flag = 1;
		return ;
	}
	if (pos.x < 0 || pos.x > size->x || pos.y < 0
		|| pos.y >= size->y
		|| temp[pos.y][pos.x] == '1')
		return ;
	temp[pos.y][pos.x] = '1';
	size->count++;
	ft_find(temp, size, (t_vector){pos.x + 1, pos.y});
	ft_find(temp, size, (t_vector){pos.x - 1, pos.y});
	ft_find(temp, size, (t_vector){pos.x, pos.y + 1});
	ft_find(temp, size, (t_vector){pos.x, pos.y - 1});
}

int	ft_flood_fill(char **tab, t_vector *size, t_vector begin)
{
	size->flag = 0;
	ft_find(tab, size, begin);
	if (size->flag)
		return (1);
	return (0);
}
