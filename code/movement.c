/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaibazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:14:56 by lgaibazz          #+#    #+#             */
/*   Updated: 2023/11/21 23:33:48 by lgaibazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Cub3d.h"

int	check_x_positive(t_game *g, float dx, float dy)
{
	if (dx > 0)
	{
		if (dy > 0)
		{
			if ((g->map.mat[(int)(g->p_x + 1)][(int)(g->p_y)] == '1')
				&& (g->map.mat[(int)(g->p_x)][(int)(g->p_y + 1)] == '1'))
				return (0);
		}
		else
		{
			if ((g->map.mat[(int)(g->p_x + 1)][(int)(g->p_y)] == '1')
				&& (g->map.mat[(int)(g->p_x)][(int)(g->p_y - 1)] == '1'))
				return (0);
		}
	}
	return (1);
}

int	check_x_negative(t_game *g, float dx, float dy)
{
	if (dx < 0)
	{
		if (dy > 0)
		{
			if ((g->map.mat[(int)(g->p_x - 1)][(int)(g->p_y)] == '1')
				&& (g->map.mat[(int)(g->p_x)][(int)(g->p_y - 1)] == '1'))
				return (0);
		}
		else
		{
			if ((g->map.mat[(int)(g->p_x - 1)][(int)(g->p_y)] == '1')
				&& (g->map.mat[(int)(g->p_x)][(int)(g->p_y + 1)] == '1'))
				return (0);
		}
	}
	return (1);
}

void	move_player(t_game *g, float dx, float dy)
{
	if ((g->map.mat[(int)floorf(g->p_x + dx)][(int)floorf(g->p_y + dy)]
		== g->map.mat[(int)floorf(g->p_x)][(int)floorf(g->p_y)]) ||
		(g->map.mat[(int)(g->p_x + dx)][(int)(g->p_y + dy)] != '1'
		&& g->map.mat[(int)(g->p_x + dx)][(int)(g->p_y + dy)] != '\0'
		&& check_x_positive(g, dx, dy) && check_x_negative(g, dx, dy)))
	{
		g->p_x += dx;
		g->p_y += dy;
	}
}

void	rotate_player(t_game *data, float angle)
{
	data->p_angle += angle;
	while (data->p_angle >= 2 * M_PI)
		data->p_angle -= 2 * M_PI;
	while (data->p_angle < 0)
		data->p_angle += 2 * M_PI;
}

int	handle_keyrelease(int keycode, t_game *data)
{
	if (keycode == 119)
		data->move_up = 0;
	else if (keycode == 100)
		data->move_right = 0;
	else if (keycode == 115)
		data->move_down = 0;
	else if (keycode == 97)
		data->move_left = 0;
	else if (keycode == 65361)
		data->turn_left = 0;
	else if (keycode == 65363)
		data->turn_right = 0;
	return (0);
}
