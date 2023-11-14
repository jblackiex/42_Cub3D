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
	data->fov = 35 * (M_PI / 180);
	if (data->orientation == 'N')
		data->p_angle = 1.5 * M_PI;
	else if (data->orientation == 'S')
		data->p_angle = 0.5 * M_PI;
	else if (data->orientation == 'E')
		data->p_angle = 0;
	else if (data->orientation == 'W')
		data->p_angle = M_PI;
	data->move_up = 0;
	data->move_down = 0;
	data->move_left = 0;
	data->move_right = 0;
	data->turn_left = 0;
	data->turn_right = 0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3D");
	data->textures[0] = load_texture(data->mlx, data->xpm[0]); // da vedere poi se posizionate in modo corretto
	data->textures[1] = load_texture(data->mlx, data->xpm[1]);
	data->textures[2] = load_texture(data->mlx, data->xpm[2]);
	data->textures[3] = load_texture(data->mlx, data->xpm[3]);
}

int	quitter(t_game *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		mlx_destroy_image(data->mlx, data->textures[i].img);
		mlx_destroy_image(data->mlx, data->textures[i].addr);
	}
	// free(data->textures);
	mlx_destroy_window(data->mlx, data->win);
	free(data->xpm);
	free(data->win);
	free(data->mlx);
	ft_free_mat(data->xpm);
	ft_free_mat(data->map.mat);
	exit(0);
	return (0);
}