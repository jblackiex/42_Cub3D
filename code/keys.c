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

int	handle_keypress(int keycode, t_game *data)
{
	float	move_speed = 0.1;
	float	rotation_speed = 0.05;

	if (keycode == 65307)
		ft_close_game(data);
	else if (keycode == 119)
		move_player(data, move_speed * cos(data->p_angle), move_speed
			* sin(data->p_angle));
	else if (keycode == 100)
		move_player(data, -move_speed * sin(data->p_angle), move_speed
			* cos(data->p_angle));
	else if (keycode == 115)
		move_player(data, -move_speed * cos(data->p_angle), -move_speed
			* sin(data->p_angle));
	else if (keycode == 97)
		move_player(data, move_speed * sin(data->p_angle), -move_speed
			* cos(data->p_angle));
	else if (keycode == 65361)
		rotate_player(data, -rotation_speed);
	else if (keycode == 65363)
		rotate_player(data, rotation_speed);
	return (0);
}

