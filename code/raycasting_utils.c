/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaibazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:16:43 by lgaibazz          #+#    #+#             */
/*   Updated: 2023/11/21 23:34:01 by lgaibazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Cub3d.h"

t_texture	load_texture(void *mlx, char *path)
{
	t_texture	texture;

	texture.img = mlx_xpm_file_to_image(mlx, path, &texture.width, &texture.height);
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel, &texture.line_length, &texture.endian);
	return (texture);
}

void	render_6(t_game *g, t_texture texture)
{
	int	color;

	g->r.wall_x -= floor(g->r.wall_x);
	g->r.tex_x = (int)(g->r.wall_x * (double)texture.width);
	if ((g->r.side == 0 && g->r.ray_dir_x > 0) || (g->r.side == 1 && g->r.ray_dir_y < 0))
		g->r.tex_x = texture.width - g->r.tex_x - 1;
	g->r.y = -1;
	while (++g->r.y < g->height)
	{
		if (g->r.y < g->r.draw_start)
			color = g->r.ceiling_color;
		else if (g->r.y >= g->r.draw_start && g->r.y < g->r.draw_end)
		{
			g->r.tex_y = (int)(g->r.y * 2 - g->height + g->r.line_height) * (double)texture.height / g->r.line_height / 2;
			color = *(int *)(texture.addr + (g->r.tex_y * texture.line_length + g->r.tex_x * (texture.bits_per_pixel / 8)));
		}
		else
			color = g->r.floor_color;
		mlx_pixel_put(g->mlx, g->win, g->r.x, g->r.y, color);
	}
}
