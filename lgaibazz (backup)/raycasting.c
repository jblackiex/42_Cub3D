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

// Structure to hold texture data
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_data
{
	int		width;
	int		height;
	int		move_up;
	int		move_down;
	int		move_left;
	int		move_right;
	int		turn_left;
	int		turn_right;
	float		p_x;
	float		p_y;
	float		fov;
	float		angle;
	float		p_angle;
	void		*mlx;
	void		*win;
	t_texture	textures[4];
}	t_data;

char map[10][10] = {
	"1111111111",
	"1000000001",
	"1000000111",
	"1000000001",
	"10000P0001",
	"1000000001",
	"1001001001",
	"1000000001",
	"1000110001",
	"1111111111"
};

int	quitter(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(data->mlx, data->textures[i].img);
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	free(data);
	exit(0);
	return (0);
}

// Function to load a texture image
t_texture	load_texture(void *mlx, char *path)
{
	t_texture	texture;

	texture.img = mlx_xpm_file_to_image(mlx, path, &texture.width, &texture.height);
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel, &texture.line_length, &texture.endian);

	return (texture);
}

void	initializer(t_data *data)
{
	data->width = 1200;
	data->height = 800;
	data->p_x = 4.5;
	data->p_y = 4.5;
	data->fov = 35 * (M_PI / 180);
	data->angle = 0;
	data->p_angle = 0;
	data->move_up = 0;
	data->move_down = 0;
	data->move_left = 0;
	data->move_right = 0;
	data->turn_left = 0;
	data->turn_right = 0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3D");
	data->textures[0] = load_texture(data->mlx, "texture/brick_black.xpm");
	data->textures[1] = load_texture(data->mlx, "texture/brick_pink.xpm");
	data->textures[2] = load_texture(data->mlx, "texture/brick_orange.xpm");
	data->textures[3] = load_texture(data->mlx, "texture/brick_lime.xpm");
}

// Function to render the scene
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

void	move_player(t_data *data, float dx, float dy)
{
	data->p_x += dx;
	data->p_y += dy;
}

void	rotate_player(t_data *data, float angle)
{
	data->p_angle += angle;
	while(data->p_angle >= 2 * M_PI)
		data->p_angle -= 2 * M_PI;
	while(data->p_angle < 0)
		data->p_angle += 2 * M_PI;
}

int	handle_keypress(int keycode, t_data *data)
{
	// Set the corresponding key state to 1 when a key is pressed
	if (keycode == 65307)
		exit(0);
	else if (keycode == 119) // W key
		data->move_up = 1;
	else if (keycode == 100) // D key
		data->move_right = 1;
	else if (keycode == 115) // S key
		data->move_down = 1;
	else if (keycode == 97) // A key
		data->move_left = 1;
	else if (keycode == 65361) // Left arrow key
		data->turn_left = 1;
	else if (keycode == 65363) // Right arrow key
		data->turn_right = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
	// Set the corresponding key state to 0 when a key is released
	if (keycode == 119)			// W key
		data->move_up = 0;
	else if (keycode == 100)		// D key
		data->move_right = 0;
	else if (keycode == 115)		// S key
		data->move_down = 0;
	else if (keycode == 97)		// A key
		data->move_left = 0;
	else if (keycode == 65361)		// Left arrow key
		data->turn_left = 0;
	else if (keycode == 65363)		// Right arrow key
		data->turn_right = 0;
	return (0);
}

int	idle_handler(t_data *data)
{
	float move_speed = 0.15;
	float rotation_speed = 0.08;

	// Update player position based on key states
	if (data->move_up)
		move_player(data, move_speed * cos(data->p_angle), move_speed * sin(data->p_angle));
	if (data->move_down)
		move_player(data, -move_speed * cos(data->p_angle), -move_speed * sin(data->p_angle));
	if (data->move_left)
		move_player(data, move_speed * sin(data->p_angle), -move_speed * cos(data->p_angle));
	if (data->move_right)
		move_player(data, -move_speed * sin(data->p_angle), move_speed * cos(data->p_angle));
	// Update player angle based on key states
	if (data->turn_left)
		rotate_player(data, -rotation_speed);
	if (data->turn_right)
		rotate_player(data, rotation_speed);
	render(data);
	usleep(16666);
	return (0);
}

int	main(void)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	initializer(data);
	render(data);
	mlx_hook(data->win, 2, 1L<<0, handle_keypress, data);
	mlx_hook(data->win, 3, 1L<<1, handle_keyrelease, data);
	mlx_hook(data->win, 17, 0, quitter, data);
	mlx_loop_hook(data->mlx, (int (*)(void *))idle_handler, data);
	mlx_loop(data->mlx);
	quitter(data);
	return (0);
}
