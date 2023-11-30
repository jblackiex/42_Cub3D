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

int	idle_handler(t_game *data)
{
	float	move_speed;
	float	rotation_speed;

	move_speed = 0.1;
	rotation_speed = 0.1;
	if (data->move_up)
		move_player(data, move_speed * cos(data->p_angle), move_speed
			* sin(data->p_angle));
	if (data->move_down)
		move_player(data, -move_speed * cos(data->p_angle), -move_speed
			* sin(data->p_angle));
	if (data->move_left)
		move_player(data, move_speed * sin(data->p_angle), -move_speed
			* cos(data->p_angle));
	if (data->move_right)
		move_player(data, -move_speed * sin(data->p_angle), move_speed
			* cos(data->p_angle));
	if (data->turn_left)
		rotate_player(data, -rotation_speed);
	if (data->turn_right)
		rotate_player(data, rotation_speed);
	render_1(data);
	usleep(16666);
	return (0);
}

int	handle_keypress(int keycode, t_game *data)
{
	if (keycode == 65307)
		quitter(data);
	else if (keycode == 119)
		data->move_up = 1;
	else if (keycode == 100)
		data->move_right = 1;
	else if (keycode == 115)
		data->move_down = 1;
	else if (keycode == 97)
		data->move_left = 1;
	else if (keycode == 65361)
		data->turn_left = 1;
	else if (keycode == 65363)
		data->turn_right = 1;
	return (0);
}
