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

void	render_5(t_game *g)
{
	t_texture	texture;

	if (g->r.side == 1)
	{
		if (g->r.ray_dir_y < 0)
			texture = g->textures[3];
		else
			texture = g->textures[2];
	}
	else
	{
		if (g->r.ray_dir_x < 0)
			texture = g->textures[0];
		else
			texture = g->textures[1];
	}
	if (g->r.side == 0)
		g->r.wall_x = g->p_y + g->r.perp_wall_dist * g->r.ray_dir_y;
	else
		g->r.wall_x = g->p_x + g->r.perp_wall_dist * g->r.ray_dir_x;
	render_6(g, texture);
}

void	render_4(t_game *g)
{
	if (g->r.side == 0)
		g->r.perp_wall_dist = (g->r.map_x - g->p_x + (1 - g->r.step_x) / 2)
			/ g->r.ray_dir_x;
	else
		g->r.perp_wall_dist = (g->r.map_y - g->p_y + (1 - g->r.step_y) / 2)
			/ g->r.ray_dir_y;
	g->r.line_height = (int)(g->height / g->r.perp_wall_dist);
	g->r.draw_start = -g->r.line_height / 2 + g->height / 2;
	if (g->r.draw_start < 0)
		g->r.draw_start = 0;
	g->r.draw_end = g->r.line_height / 2 + g->height / 2;
	if (g->r.draw_end >= g->height)
		g->r.draw_end = g->height - 1;
	render_5(g);
}

void	render_3(t_game *g)
{
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
		if (&g->map.mat[g->r.map_x][g->r.map_y]
			&& g->map.mat[g->r.map_x][g->r.map_y] == '1')
			g->r.hit = 1;
	}
	render_4(g);
}

void	render_2(t_game *g)
{
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
	g->r.hit = 0;
	render_3(g);
}

void	render_1(t_game *g)
{
	g->r.floor_color = g->map.rgb[0].color[0] * 65536 + g->map.rgb[0].color[1]
		* 256 + g->map.rgb[0].color[2];
	g->r.ceiling_color = g->map.rgb[1].color[0] * 65536 + g->map.rgb[1].color[1]
		* 256 + g->map.rgb[1].color[2];
	g->r.x = -1;
	while (++g->r.x < g->width)
	{
		g->r.camera_x = 2 * g->r.x / (double)g->width - 1;
		g->r.ray_dir_x = cos(g->p_angle + g->fov * g->r.camera_x);
		g->r.ray_dir_y = sin(g->p_angle + g->fov * g->r.camera_x);
		g->r.map_x = (int)g->p_x;
		g->r.map_y = (int)g->p_y;
		g->r.delta_dist_x = fabs(1 / g->r.ray_dir_x);
		g->r.delta_dist_y = fabs(1 / g->r.ray_dir_y);
		render_2(g);
	}
}
