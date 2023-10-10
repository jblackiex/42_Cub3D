/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:43:33 by nbordoni          #+#    #+#             */
/*   Updated: 2023/02/12 15:43:35 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Cub3d.h"

void	ft_free_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	**get_map(char *mapy)
{
	char	**result;
	char	*holder;
	char	*old_address;
	char	*map;
	int		fd;

	fd = open(mapy, O_RDONLY);
	if (fd == -1)
		print_error(fd, NULL);
	map = ft_strdup("");
	while (1)
	{
		holder = get_next_line(fd);
		if (!holder)
			break ;
		old_address = map;
		map = ft_strjoin(old_address, holder);
		ft_free_ptr((void *)&old_address);
		ft_free_ptr((void *)&holder);
	}
	result = ft_split_mod(map, '\n');
	ft_free_ptr((void *)&map);
	return (close(fd), result);
}

// void	print2(t_game *g, char c, int x, int y)
// {
// 	if (c == 'F' && g->moves && ((g->w != 'a' && g->w != 's')
// 			|| (g->c_cur >= (g->c_max / 2))))
// 	{
// 		if (ft_check_enemy(g, x, y))
// 		{
// 			write(1, "\nGAME OVER!\n", 12);
// 			ft_close_game(g);
// 		}
// 		ft_print_sprite(g, g->sprites.enemy1, g->sprite_pos);
// 	}
// 	else if (c == 'F')
// 		ft_print_sprite(g, g->sprites.enemy1, g->sprite_pos);
// 	else if (g->w == 'a' && c == 'K')
// 		ft_print_sprite(g, g->sprites.floorx, g->sprite_pos);
// 	else if (g->w == 'a')
// 		ft_print_sprite(g, g->sprites.heroa, g->sprite_pos);
// 	else if (g->w == 's' && c == 'K')
// 		ft_print_sprite(g, g->sprites.floorx, g->sprite_pos);
// 	else if (g->w == 's')
// 		ft_print_sprite(g, g->sprites.heros, g->sprite_pos);
// 	else if (g->w == 'w')
// 		ft_print_sprite(g, g->sprites.herow, g->sprite_pos);
// 	else if (g->w == 'p')
// 		ft_print_sprite(g, g->sprites.herod, g->sprite_pos);
// }

// static int	ft_core_print(char c, t_game *g, int x, int y)
// {
// 	if (c == '1')
// 		ft_print_sprite(g, g->sprites.wall, g->sprite_pos);
// 	else if (c == '0' && (g->w == 'a' && g->c_cur == g->c_max))
// 		ft_print_sprite(g, g->sprites.hero2, g->sprite_pos);
// 	else if (c == '0')
// 		ft_print_sprite(g, g->sprites.floor, g->sprite_pos);
// 	else if (c == 'C')
// 		ft_print_sprite(g, g->sprites.coll, g->sprite_pos);
// 	else if (c == 'P')
// 		ft_print_sprite(g, g->sprites.herod, g->sprite_pos);
// 	else if (c == 'E' && (g->c_cur == g->c_max))
// 		ft_print_sprite(g, g->sprites.doorspecial, g->sprite_pos);
// 	else if (c == 'E')
// 		ft_print_sprite(g, g->sprites.exit1, g->sprite_pos);
// 	else if (c == 'N')
// 		ft_print_sprite(g, g->sprites.hero2, g->sprite_pos);
// 	else
// 		print2(g, c, x, y);
// 	return (0);
// }

// int	ft_display_mat(t_game *g)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	g->sprite_pos.y = 0;
// 	while (y < g->map.size.y)
// 	{
// 		x = 0;
// 		g->sprite_pos.x = 0;
// 		while (x < g->map.size.x)
// 		{
// 			ft_core_print(g->map.mat[y][x], g, x, y);
// 			x++;
// 			g->sprite_pos.x += g->sprites.size.x;
// 		}
// 		y++;
// 		g->sprite_pos.y += g->sprites.size.y;
// 	}
// 	return (0);
// }
