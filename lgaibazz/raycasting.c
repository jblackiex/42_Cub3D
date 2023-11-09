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

typedef struct s_data
{
	int		width;
	int		height;
	float	p_x;
	float	p_y;
	float	fov;
	float	angle;
	float	p_angle;
	void	*mlx;
	void	*win;
	
}	t_data;

char	map[10][10] = {
    "1111111111",
    "1000000001",
    "1000000001",
    "1000000001",
    "10000P0001",
    "1000000001",
    "1001001001",
    "1000000001",
    "1000000001",
    "1111111111"
};

int	quitter(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data);
	exit(0);
	return (0);
}

void	initializer(t_data *data)
{
	data->width = 1200;
	data->height = 800;
	data->p_x = 4.5;
	data->p_y = 4.5;
	data->fov = 90 * (M_PI / 180);
	data->angle = 0;
	data->p_angle = 0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3D");
}

void	render(t_data *data)
{
	int		x;
	int		y;
	int		floor_color = 0x404040;
	int		ceiling_color = 0x808080;

	x = -1;
	while (++x < data->width)
	{
		double	camera_x = 2 * x / (double)data->width - 1; // Camera space x-coordinate
		double	ray_dir_x = cos(data->p_angle) + data->fov * camera_x;
		double	ray_dir_y = sin(data->p_angle) + data->fov * camera_x;
		
		// Calculate the map position for the current ray
		int	map_x = (int)data->p_x;
		int	map_y = (int)data->p_y;

		// Calculate the length of the ray from the current position to the next grid line
		double	delta_dist_x = fabs(1 / ray_dir_x);
		double	delta_dist_y = fabs(1 / ray_dir_y);

		// Calculate the step direction and initial side distances to the next grid line
		int	step_x;
		int	step_y;
		double	side_dist_x;
		double	side_dist_y;
		
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

		// Perform Digital Differential Analysis (DDA) to find the first wall hit
		int	hit = 0;
		int	side; // 0 for horizontal, 1 for vertical
		double	perp_wall_dist;
		
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
			
			if (map[map_x][map_y] == '1')
				hit = 1;
		}

		// Calculate the perpendicular distance to the wall
		if (side == 0)
			perp_wall_dist = (map_x - data->p_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - data->p_y + (1 - step_y) / 2) / ray_dir_y;

		// Calculate the height of the wall segment based on the perpendicular distance
		int	line_height = (int)(data->height / perp_wall_dist);

		// Calculate the starting and ending points on the screen for the wall segment
		int	draw_start = -line_height / 2 + data->height / 2;
		if (draw_start < 0)
			draw_start = 0;
		int	draw_end = line_height / 2 + data->height / 2;
		if (draw_end >= data->height)
			draw_end = data->height - 1;

		// Render the wall segment
		int wall_color;
		if (side == 1)
		{
			if (ray_dir_y < 0)
				wall_color = 0xFF0000; // Red for walls facing north
			else
				wall_color = 0x0000FF; // Blue for walls facing south
		}
		else
		{
			if (ray_dir_x < 0)
				wall_color = 0x00FF00; // Green for walls facing west
			else
				wall_color = 0xFFFF00; // Yellow for walls facing east
		}
		y = -1;
		while (++y < data->height)
		{
			if (y < draw_start) // Ceiling
				mlx_pixel_put(data->mlx, data->win, x, y, ceiling_color);
			else if (y >= draw_start && y < draw_end) // Wall
				mlx_pixel_put(data->mlx, data->win, x, y, wall_color); // Color from the wall rendering
			else // Floor
				mlx_pixel_put(data->mlx, data->win, x, y, floor_color);
		}
	}
}

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

int	handle_keypress(int keycode, t_data *data)
{
	float	move_speed = 0.1;
	float	rotation_speed = 0.05;

	if (keycode == 65307)
		quitter(data);
	else if (keycode == 119)
		move_player(data, move_speed * cos(data->p_angle), move_speed * sin(data->p_angle));
	else if (keycode == 100)
		move_player(data, -move_speed * sin(data->p_angle), move_speed * cos(data->p_angle));
	else if (keycode == 115)
		move_player(data, -move_speed * cos(data->p_angle), -move_speed * sin(data->p_angle));
	else if (keycode == 97)
		move_player(data, move_speed * sin(data->p_angle), -move_speed * cos(data->p_angle));
	else if (keycode == 65361)
		rotate_player(data, -rotation_speed);
	else if (keycode == 65363)
		rotate_player(data, rotation_speed);
	return (0);
}

int	main(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	initializer(data);
	render(data);
	mlx_do_key_autorepeaton(data->mlx);
	mlx_hook(data->win, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win, 17, 0, quitter, data);
	mlx_loop_hook(data->mlx, (int (*)(void *))idle_handler, data);
	mlx_loop(data->mlx);
	quitter(data);
	return (0);
}
