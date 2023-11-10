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

void	initializer(t_game *data)
{
	data->width = 1200;
	data->height = 800;
	data->p_x = (float)data->s_pos.x + 0.5;
	data->p_y = (float)data->s_pos.y + 0.5;
	data->fov = 90 * (M_PI / 180);
	data->angle = 0;
	data->p_angle = 0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3D");
}