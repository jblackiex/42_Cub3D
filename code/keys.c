/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:42:59 by nbordoni          #+#    #+#             */
/*   Updated: 2023/02/12 15:43:03 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Cub3d.h"

static int	ft_event_check(char next_pos, t_game *g)
{
	if (next_pos == 'F')
	{
		write(1, "\nGAME OVER!\n", 12);
		ft_close_game(g);
	}
	if (next_pos == 'E')
	{
		write(1, "\nVICTORY!\n", 10);
		ft_close_game(g);
	}
	if (next_pos == 'C')
	{
		g->c_cur++;
		if (g->c_cur == g->c_max)
			g->fire = 1;
		else if (g->c_cur >= (g->c_max / 2))
			g->fire = 2;
	}
	return (0);
}

static int	ft_update_stats(t_game *g)
{
	ft_stats(g, 0xFFFFFF);
	ft_printf("\rMoves = %d", g->moves);
	ft_printf("\tCollectibles = %d", g->c_cur);
	return (0);
}

static int	ft_events(char next_pos, int x, int y, t_game *g)
{
	if (next_pos == '0' || next_pos == 'C' || next_pos == 'F'
		|| (next_pos == 'E' && g->c_cur == g->c_max))
	{
		ft_stats(g, 0x000000);
		g->moves++;
		ft_event_check(next_pos, g);
		ft_update_stats(g);
		if (g->fire == 1)
			g->map.mat[y][x] = 'N';
		else if (g->fire == 2)
			g->map.mat[y][x] = 'K';
		else if (g->w != 'p')
			g->map.mat[y][x] = 'A';
		else if (g->fire != 1)
			g->map.mat[y][x] = 'P';
		g->map.mat[g->hero_pos.y][g->hero_pos.x] = '0';
		g->hero_pos.x = x;
		g->hero_pos.y = y;
	}
	return (0);
}

static int	ft_dealy(t_game *g)
{
	if (g->w == 'w')
		ft_events(g->map.mat[g->hero_pos.y - 1][g->hero_pos.x],
			g->hero_pos.x, g->hero_pos.y - 1, g);
	else if (g->w == 'a')
		ft_events(g->map.mat[g->hero_pos.y][g->hero_pos.x - 1],
			g->hero_pos.x - 1, g->hero_pos.y, g);
	else if (g->w == 's')
		ft_events(g->map.mat[g->hero_pos.y + 1][g->hero_pos.x],
			g->hero_pos.x, g->hero_pos.y + 1, g);
	else if (g->w == 'p')
		ft_events(g->map.mat[g->hero_pos.y][g->hero_pos.x + 1],
			g->hero_pos.x + 1, g->hero_pos.y, g);
	return (0);
}

int	ft_core_keys(int tasto, t_game *g)
{
	if (tasto == 65307)
		ft_close_game(g);
	else if (tasto == 'w' || tasto == 65362)
		g->w = 'w';
	else if (tasto == 'a' || tasto == 65361)
		g->w = 'a';
	else if (tasto == 's' || tasto == 65364)
		g->w = 's';
	else if (tasto == 'd' || tasto == 65363)
		g->w = 'p';
	else
		return (0);
	ft_dealy(g);
	return (0);
}
