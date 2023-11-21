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

t_texture	load_texture(void *mlx, char *path)
{
	t_texture	texture;

	texture.img = mlx_xpm_file_to_image(mlx, path, &texture.width, &texture.height);
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel, &texture.line_length, &texture.endian);

	return (texture);
}

void	render(t_game *g)
{
	g->r.floor_color = g->map.rgb[0].color[0] * 65536 + g->map.rgb[0].color[1] * 256 + g->map.rgb[0].color[2];
	g->r.ceiling_color = g->map.rgb[1].color[0] * 65536 + g->map.rgb[1].color[1] * 256 + g->map.rgb[1].color[2];

	g->r.x = -1;
	while (++g->r.x < g->width)
	{
		g->r.camera_x = 2 * g->r.x / (double)g->width - 1;
		g->r.ray_dir_x = cos(g->p_angle + g->fov * g->r.camera_x);
		g->r.ray_dir_y = sin(g->p_angle + g->fov * g->r.camera_x);

		// Map position
		g->r.map_x = (int)g->p_x;
		g->r.map_y = (int)g->p_y;

		// Length of ray from one x or y-side to next x or y-side
		g->r.delta_dist_x = fabs(1 / g->r.ray_dir_x);
		g->r.delta_dist_y = fabs(1 / g->r.ray_dir_y);

		// Calculate step and initial sideDist
		if (g->r.ray_dir_x < 0)
		{
			g->r.step_x = -1;
			g->r.side_dist_x = (g->p_x - g->r.map_x) * g->r.delta_dist_x;
		}
		else
		{
			g->r.step_x = 1;
			g->r.side_dist_x = (g->r.map_x + 1.0 - g->p_x) * g->r.delta_dist_x;
		}

		if (g->r.ray_dir_y < 0)
		{
			g->r.step_y = -1;
			g->r.side_dist_y = (g->p_y - g->r.map_y) * g->r.delta_dist_y;
		}
		else
		{
			g->r.step_y = 1;
			g->r.side_dist_y = (g->r.map_y + 1.0 - g->p_y) * g->r.delta_dist_y;
		}

		// Perform DDA
		g->r.hit = 0;
		while (!g->r.hit)
		{
			if (g->r.side_dist_x < g->r.side_dist_y)
			{
				g->r.side_dist_x += g->r.delta_dist_x;
				g->r.map_x += g->r.step_x;
				g->r.side = 0;
			}
			else
			{
				g->r.side_dist_y += g->r.delta_dist_y;
				g->r.map_y += g->r.step_y;
				g->r.side = 1;
			}

			if (g->map.mat[g->r.map_x][g->r.map_y] == '1')
				g->r.hit = 1;
		}
		// Calculate the perpendicular distance to the wall
		if (g->r.side == 0)
			g->r.perp_wall_dist = (g->r.map_x - g->p_x + (1 - g->r.step_x) / 2) / g->r.ray_dir_x;
		else
			g->r.perp_wall_dist = (g->r.map_y - g->p_y + (1 - g->r.step_y) / 2) / g->r.ray_dir_y;

		// Calculate the height of the wall segment based on the perpendicular distance
		g->r.line_height = (int)(g->height / g->r.perp_wall_dist);

		// Calculate the starting and ending points on the screen for the wall segment
		g->r.draw_start = -g->r.line_height / 2 + g->height / 2;
		if (g->r.draw_start < 0)
			g->r.draw_start = 0;
		g->r.draw_end = g->r.line_height / 2 + g->height / 2;
		if (g->r.draw_end >= g->height)
			g->r.draw_end = g->height - 1;
		// Determine the wall color based on its orientation
		t_texture texture;
		if (g->r.side == 1)
		{
			if (g->r.ray_dir_y < 0)
				texture = g->textures[0]; // Texture for walls facing north
			else
				texture = g->textures[1]; // Texture for walls facing south
		}
		else
		{
			if (g->r.ray_dir_x < 0)
				texture = g->textures[2]; // Texture for walls facing west
			else
				texture = g->textures[3]; // Texture for walls facing east
		}
		// Map the texture onto the wall
		if (g->r.side == 0)
			g->r.wall_x = g->p_y + g->r.perp_wall_dist * g->r.ray_dir_y;
		else
			g->r.wall_x = g->p_x + g->r.perp_wall_dist * g->r.ray_dir_x;

		g->r.wall_x -= floor(g->r.wall_x);
		g->r.tex_x = (int)(g->r.wall_x * (double)texture.width);
		if ((g->r.side == 0 && g->r.ray_dir_x > 0) || (g->r.side == 1 && g->r.ray_dir_y < 0))
			g->r.tex_x = texture.width - g->r.tex_x - 1;
		// Render the floor and ceiling
		g->r.y = -1;
		while (++g->r.y < g->height)
		{
			int color;
			if (g->r.y < g->r.draw_start) // Ceiling
				color = g->r.ceiling_color;
			else if (g->r.y >= g->r.draw_start && g->r.y < g->r.draw_end) // Wall
			{
				g->r.tex_y = (int)(g->r.y * 2 - g->height + g->r.line_height) * (double)texture.height / g->r.line_height / 2;
				color = *(int *)(texture.addr + (g->r.tex_y * texture.line_length + g->r.tex_x * (texture.bits_per_pixel / 8)));
			}
			else // Floor
				color = g->r.floor_color;
			mlx_pixel_put(g->mlx, g->win, g->r.x, g->r.y, color);
		}
	}
}
