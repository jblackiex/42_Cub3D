/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:43:10 by nbordoni          #+#    #+#             */
/*   Updated: 2023/02/12 15:43:13 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Cub3d.h"

void	find_player(t_game *g)
{
	int	x;
	int	y;

	y = -1;
	while (++y < g->map.size.y)
	{
		x = -1;
		while (g->map.mat[y] && g->map.mat[y][++x])
		{
			if (g->map.mat[y][x] == 'N' || g->map.mat[y][x] == 'S' ||
				g->map.mat[y][x] == 'W' || g->map.mat[y][x] == 'E')
			{
				g->p_x = (float)y + 0.5;
				g->p_y = (float)x + 0.5;
				break ;
			}
		}
	}
}