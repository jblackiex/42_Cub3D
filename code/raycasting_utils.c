/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaibazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:14:56 by lgaibazz          #+#    #+#             */
/*   Updated: 2023/10/27 17:14:58 by lgaibazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Cub3d.h"

int	idle_handler(t_game *data)
{
	float	move_speed = 0.15;
	float	rotation_speed = 0.08;

	if (data->move_up)
		move_player(data, move_speed * cos(data->p_angle), move_speed * sin(data->p_angle));
	if (data->move_down)
		move_player(data, -move_speed * cos(data->p_angle), -move_speed * sin(data->p_angle));
	if (data->move_left)
		move_player(data, move_speed * sin(data->p_angle), -move_speed * cos(data->p_angle));
	if (data->move_right)
		move_player(data, -move_speed * sin(data->p_angle), move_speed * cos(data->p_angle));
	if (data->turn_left)
		rotate_player(data, -rotation_speed);
	if (data->turn_right)
		rotate_player(data, rotation_speed);
	render(data);
	usleep(16666);
	return (0);
}

void	move_player(t_game *data, float dx, float dy)
{
	if (data->map.mat[(int)(data->p_x + dx)][(int)(data->p_y + dy)] != '1')
	{
		data->p_x += dx;
		data->p_y += dy;
	}
}

void	rotate_player(t_game *data, float angle)
{
	data->p_angle += angle;
	while(data->p_angle >= 2 * M_PI)
		data->p_angle -= 2 * M_PI;
	while(data->p_angle < 0)
		data->p_angle += 2 * M_PI;
}

int	handle_keypress(int keycode, t_game *data)
{
	if (keycode == 65307)
		exit(0);
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
