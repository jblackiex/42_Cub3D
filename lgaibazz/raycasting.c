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

#define S_WIDTH 800
#define S_HEIGHT 400
#define M_WIDTH 800
#define M_HEIGHT 600
#define PLAYER_SIZE 1

int		mapHeight = 8;
int		mapWidth = 8;
int		playerX;
int		playerY;
float	playerAngle;
float	tileSize = 3;

char	map[8][8] = {
    {'1','1','1','1','1','1','1','1'},
    {'1','0','0','0','0','0','0','1'},
    {'1','0','S','0','1','1','0','1'},
    {'1','0','0','0','0','0','0','1'},
    {'1','0','1','0','1','1','0','1'},
    {'1','0','0','0','0','1','0','1'},
    {'1','0','1','1','0','0','0','1'},
    {'1','1','1','1','1','1','1','1'}
};

void render_scene(void *mlx_ptr, void *win_ptr)
{
    int x;
    int y;

    y = 0;
    while (y < S_HEIGHT)
    {
        x = 0;
        while (x < S_WIDTH)
        {
            int hitWall = 0;
            float distanceToWall = 0;
            float rayAngle = (playerAngle - 0.5) + ((float)x / (float)S_WIDTH);
            float stepSize = 0.1;
            float eyeX = sin(rayAngle);
            float eyeY = cos(rayAngle);

            while (!hitWall && distanceToWall < 16)
            {
                distanceToWall += stepSize;
                int testX = (int)(playerX + eyeX * distanceToWall);
                int testY = (int)(playerY + eyeY * distanceToWall);
                if (testX < 0 || testX >= mapWidth || testY < 0 || testY >= mapHeight)
                {
                    hitWall = 1;
                    distanceToWall = 16;
                }
                else if (map[testY][testX] == '1')
                    hitWall = 1;
            }
            int ceiling = (S_HEIGHT / 2) - (S_HEIGHT / distanceToWall);
            int floor = S_HEIGHT - ceiling;
            if (y <= ceiling)
                mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x000000); // Black color for ceiling
            else if (y > ceiling && y <= floor)
            {
                float wallX = playerX + eyeX * distanceToWall;
                float wallY = playerY + eyeY * distanceToWall;
                float wallAngle = atan2(wallY - playerY, wallX - playerX);
                if (wallAngle < 0)
                    wallAngle += 2 * M_PI;
                int wallColor;
                if (wallAngle >= 0 && wallAngle < M_PI / 2)
                    wallColor = 0xFF0000; // Red color for walls facing east
                else if (wallAngle >= M_PI / 2 && wallAngle < M_PI)
                    wallColor = 0x00FF00; // Green color for walls facing south
                else if (wallAngle >= M_PI && wallAngle < 3 * M_PI / 2)
                    wallColor = 0x0000FF; // Blue color for walls facing west
                else
                    wallColor = 0xFFFF00; // Yellow color for walls facing north
                mlx_pixel_put(mlx_ptr, win_ptr, x, y, wallColor);
            }
            else
                mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x808080); // Gray color for floor
            x++;
        }
        y++;
    }
}

int	move_player(int keycode)
{
	if (keycode == 123)
		playerAngle -= 0.1;
	if (keycode == 124)
		playerAngle += 0.1;
	return (1);
}

int main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

    // Find player position and facing direction in the map
    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
            {
                playerX = j * tileSize + tileSize / 2; // Place the player at the center of the tile horizontally
                playerY = i * tileSize + tileSize / 2; // Place the player at the center of the tile vertically
                if (map[i][j] == 'N')
					playerAngle = 0;
				else if (map[i][j] == 'S')
					playerAngle = 3.14159;
				else if (map[i][j] == 'E')
					playerAngle = 1.5708;
				else if (map[i][j] == 'W')
					playerAngle = 4.71239;
				break;
            }
        }
    }
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, S_WIDTH, S_HEIGHT, "Cub3d");

    // Render della scena iniziale
    render_scene(mlx_ptr, win_ptr);

    // Event loop
    while (true)
    {
        // Gestione rotazione e movimento player (non sono riuscito a finirlo!)
		mlx_key_hook(win_ptr, move_player, NULL);

        // Re-render the scene with updated player position and rotation
        render_scene(mlx_ptr, win_ptr);

        // Wait for the next frame
        usleep(16667); // 60 FPS
    }
    // Close the window and cleanup
    mlx_destroy_window(mlx_ptr, win_ptr);
    mlx_destroy_display(mlx_ptr);

    return 0;
}
