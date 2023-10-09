/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:42:35 by nbordoni          #+#    #+#             */
/*   Updated: 2023/02/12 15:42:37 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Cub3d.h"

int	ft_stats(t_game *g, int color)
{
	char	*str;
	char	*str2;
	char	*str3;
	char	*str4;

	str2 = ft_itoa(g->moves);
	str = ft_strjoin("Moves: ", str2);
	mlx_string_put(g->game.mlx, g->game.win, 20, 12, color, str);
	str3 = ft_itoa(g->c_cur);
	str4 = ft_strjoin("Collectibles: ", str3);
	mlx_string_put(g->game.mlx, g->game.win, 10, 27, color, str4);
	free(str2);
	free(str);
	free(str3);
	free(str4);
	return (0);
}

int	ft_checky_enemy(t_game *g, int x, int y)
{
	if ((g->map.mat[y][x + 1] == '0' || g->map.mat[y][x + 1] == 'P'
			|| g->map.mat[y][x + 1] == 'K') && x != g->x1)
	{
		if (g->map.mat[y][x + 1] == 'P' || g->map.mat[y][x + 1] == 'K')
			return (1);
		g->map.mat[y][x] = '0';
		g->map.mat[y][x + 1] = 'F';
		x++;
		g->sprite_pos.x += g->sprites.size.x;
	}
	else if ((g->map.mat[y][x - 1] == '0'
		|| g->map.mat[y][x - 1] == 'A') && x != g->x2)
	{
		if (g->map.mat[y][x + 1] == 'A' || g->map.mat[y][x + 1] == 'K'
			|| g->map.mat[y][x + 1] == 'P')
			return (1);
		g->x1 = x - 2;
		g->map.mat[y][x] = '0';
		g->map.mat[y][x - 1] = 'F';
		x--;
		g->sprite_pos.x -= g->sprites.size.x;
	}
	return (0);
}
