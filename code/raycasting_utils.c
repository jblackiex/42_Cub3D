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

int	idle_handler(t_data *data)
{
	render(data);
}

void	move_player(t_data *data, float dx, float dy)
{
	data->p_x += dx;
	data->p_y += dy;
	mlx_clear_window(data->mlx, data->win);
	render(data);
}

void	rotate_player(t_data *data, float angle)
{
	data->p_angle += angle;
	mlx_clear_window(data->mlx, data->win);
	render(data);
}

int	quitter(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data);
	exit(0);
	return (0);
}
