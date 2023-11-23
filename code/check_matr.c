/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_matr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:43:22 by nbordoni          #+#    #+#             */
/*   Updated: 2023/02/12 15:43:25 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Cub3d.h"

static int	ft_char_check(t_game *g, int count, int x, int y)
{
	while (++y < g->map.size.y)
	{
		x = -1;
		while (g->map.mat[y] && g->map.mat[y][++x])
		{
			if ((g->map.mat[y][x] != 'N' && g->map.mat[y][x] != 'S'
					&& g->map.mat[y][x] != 32 && g->map.mat[y][x] != '	'
					&& g->map.mat[y][x] != 'W' && g->map.mat[y][x] != 'E'
					&& g->map.mat[y][x] != '0' && g->map.mat[y][x] != '1'
					&& g->map.mat[y][x] != '\n')
					|| count > 1)
				return (1);
			else if (g->map.mat[y][x] == 'N' || g->map.mat[y][x] == 'S' ||
					g->map.mat[y][x] == 'W' || g->map.mat[y][x] == 'E')
			{
				g->s_pos.x = x;
				g->s_pos.y = y;
				g->orientation = g->map.mat[y][x];
				count++;
			}
		}
	}
	if (count != 1)
		return (printf("\033[1;31mError\n Missing player char\n\033[0m"), 1);
	return (0);
}

static void	ft_mat_size(char **mat, t_mat *t)
{
	int	i;

	i = 0;
	while (mat[i])
		i++;
	t->size.y = --i;
}

static void	print_map(char **map)
{
	int	i;

	i = 0;
	while(map[i])
		printf("map[%d] = %s\n", i, map[i++]);

}

char	**get_map_cub(char **map, t_mat *t)
{
	int		i;
	int		j;
	char	**map_real;

	i = 0;
	j = 0;
	while (map[i] && i < t->i)
		i++;
	if (!map[i])
	{
		printf("Error\n No map inside .cub file\n");
		ft_free_mat(map); // funzione freea tutto
		exit (1);
	}
	map_real = (char **) ft_calloc(t->size.y + 2, sizeof(char *));
	while (map[i])
		map_real[j++] = ft_strdup(map[i++]);
	map_real[j] = NULL;
	// print_map(map_real);
	// exit(0);
	return (map_real);
}

static int	copy_rgb(t_game *var, t_mat *matr)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		var->map.rgb[0].color[i] = matr->rgb[0].color[i];
		var->map.rgb[1].color[i] = matr->rgb[1].color[i];
		i++;
	}
	return (1);
}

void	check_core(char *str, t_game *var)
{
	t_mat	matr;
	t_mat	tmp;
	int		flag;
	int		x;
	int		y;

	flag = 0;
	x = 0;
	y = -1;
	tmp.fl = 0;
	matr.mat = get_map(str);
	ft_mat_size(matr.mat, &matr);
	check_cub_core(&tmp, var, &matr);
	ft_mat_size(&tmp.mat[tmp.i], &tmp);
	var->map.size.y = tmp.size.y;
	var->map.mat = get_map_cub(tmp.mat, &tmp);
	// print_map(var->map.mat);
	// exit(0);
	if (ft_char_check(var, 0, x, y))
		flag = printf("\033[1;31mError\n Wrong elements inside map\n\033[0m");
	x = var->s_pos.x;
	y = var->s_pos.y;
	if (!flag && ft_path_check(var, &tmp))
		flag = printf("\033[1;31m Check map inside .cub file\n\033[0m");
	if (ft_free_mat(tmp.mat) && ft_free_mat(matr.mat) && copy_rgb(var, &tmp)
		&& flag && ft_free_mat(var->map.mat))
		exit(1);
}
