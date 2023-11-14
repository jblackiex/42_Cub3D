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

void	render(t_game *data)
{
	int		x;
	int		y;

	int		floor_color = data->map.rgb[0].color[0] * 65536 + data->map.rgb[0].color[1] * 256 + data->map.rgb[0].color[2];
	int		ceiling_color = data->map.rgb[1].color[0] * 65536 + data->map.rgb[1].color[1] * 256 + data->map.rgb[1].color[2];

	x = -1;
	while (++x < data->width)
	{
		double camera_x = 2 * x / (double)data->width - 1;
		double ray_dir_x = cos(data->p_angle + data->fov * camera_x);
		double ray_dir_y = sin(data->p_angle + data->fov * camera_x);

		// Map position
		int map_x = (int)data->p_x;
		int map_y = (int)data->p_y;

		// Length of ray from one x or y-side to next x or y-side
		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);

		// Calculate step and initial sideDist
		int step_x, step_y;
		double side_dist_x, side_dist_y;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->p_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->p_x) * delta_dist_x;
		}

		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->p_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->p_y) * delta_dist_y;
		}

		// Perform DDA
		int hit = 0;
		int side;
		double perp_wall_dist;

		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}

			if (data->map.mat[map_x][map_y] == '1')
				hit = 1;
		}

		// Calculate the perpendicular distance to the wall
		if (side == 0)
			perp_wall_dist = (map_x - data->p_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - data->p_y + (1 - step_y) / 2) / ray_dir_y;

		// Calculate the height of the wall segment based on the perpendicular distance
		int line_height = (int)(data->height / perp_wall_dist);

		// Calculate the starting and ending points on the screen for the wall segment
		int draw_start = -line_height / 2 + data->height / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + data->height / 2;
		if (draw_end >= data->height)
			draw_end = data->height - 1;

		// Determine the wall color based on its orientation
		int wall_color;
		t_texture texture;

		if (side == 1)
		{
			if (ray_dir_y < 0)
				texture = data->textures[0]; // Texture for walls facing north
			else
				texture = data->textures[1]; // Texture for walls facing south
		}
		else
		{
			if (ray_dir_x < 0)
				texture = data->textures[2]; // Texture for walls facing west
			else
				texture = data->textures[3]; // Texture for walls facing east
		}

		// Map the texture onto the wall
		double wall_x;
		if (side == 0)
			wall_x = data->p_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = data->p_x + perp_wall_dist * ray_dir_x;

		wall_x -= floor(wall_x);

		int tex_x = (int)(wall_x * (double)texture.width);
		if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
			tex_x = texture.width - tex_x - 1;

		// Render the floor and ceiling
		y = -1;
		while (++y < data->height)
		{
			int color;
			if (y < draw_start) // Ceiling
				color = ceiling_color;
			else if (y >= draw_start && y < draw_end) // Wall
			{
				int tex_y = (int)(y * 2 - data->height + line_height) * (double)texture.height / line_height / 2;
				color = *(int *)(texture.addr + (tex_y * texture.line_length + tex_x * (texture.bits_per_pixel / 8)));
			}
			else // Floor
				color = floor_color;

			mlx_pixel_put(data->mlx, data->win, x, y, color);
		}
	}
}
