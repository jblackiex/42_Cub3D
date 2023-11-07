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

void	quitter(t_data *data)
{
	free(data);
	exit(0);
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

	x = -1;
	while (++x < data->width)
	{
		double	angle = data->p_angle - (data->fov / 2) + (x / (double)data->width) * data->fov;
		double	r_x = data->p_x;
	 	double	r_y = data->p_y;
		double	r_dir_x = cos(angle);
		double	r_dir_y = sin(angle);

		// Perform raycasting and collision detection with the map.
		int	hit_wall = 0;
		while (!hit_wall)
		{
			int	m_x = (int)r_x;
			int	m_y = (int)r_y;
	
			// Check if the ray hits a wall.
			if (map[m_x][m_y] == '1')
			{
				hit_wall = 1;
				// Calculate the distance from the player to the wall.
				double	wall_dist = sqrt((r_x - data->p_x) * (r_x - data->p_x) + (r_y - data->p_y) * (r_y - data->p_y));
				// Calculate the height of the wall segment based on the distance.
				int	wall_height = (int)(data->height / wall_dist);
	
				// Calculate the position of the wall segment on the screen.
				int	wall_screen_x = x;
				int	wall_screen_height = wall_height;
				// Calculate the top and bottom of the wall segment.
				int	wall_screen_top = (data->height - wall_height) / 2;
				int	wall_screen_bottom = (data->height + wall_height) / 2;
				// Render the wall segment on the screen.
				y = -1;
				while (++y < data->height)
				{
					if (y < wall_screen_top)
						mlx_pixel_put(data->mlx, data->win, x, y, 0x66FFFF); // Above the wall
					else if (y >= wall_screen_top && y < wall_screen_bottom)
						mlx_pixel_put(data->mlx, data->win, x, y, 0xFF0000); // Wall
					else
						mlx_pixel_put(data->mlx, data->win, x, y, 0x006600); // Below the wall
				}
			}
			// Move the ray to the next grid square.
			r_x += r_dir_x;
			r_y += r_dir_y;
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
    render(data);
}

void	rotate_player(t_data *data, float angle)
{
    data->p_angle += angle;
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
	mlx_key_hook(data->win, handle_keypress, data);
	mlx_loop_hook(data->mlx, (int (*)(void *))idle_handler, data);
	mlx_loop(data->mlx);
	quitter(data);
	return (0);
}
