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
					&& g->map.mat[y][x] != 32 && g->map.mat[y][x] != '\t'
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
	int	row;

	i = 0;
	row = 0;
	while (mat[i])
	{
		t->size.x = ft_strlen(mat[i]);
		if (t->size.x > row)
			row = t->size.x;
		i++;
	}
	//donnow if id be better to store all rows or just the big one
	t->size.y = --i;
	t->size.x = row;
}

char **get_map_cub(char **map, t_mat *t)
{
	int	i;
	int	j;
	char **map_real;

	i = 0;
	j = 0;
	while (map[i] && i < t->i)
		i++;
	if (!map[i])
	{
		printf("Error\n No map inside .cub file\n");
		ft_free_mat(map);
		exit (1);
	}
	map_real = (char **) ft_calloc(t->size.y + 2, sizeof(char *)); // here instead of 9 i should ve set the num of rows
	while (map[i])
		map_real[j++] = ft_strdup(map[i++]);
	map_real[j] = NULL;
	return (map_real);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while(map[i])
		printf("map[%d] = %s\n", i, map[i++]);

}

void	check_core(char *str, t_game *var)
{
	t_mat	matr;
	int		flag;
	int		x;
	int		y;

	flag = 0;
	x = 0;
	y = -1;
	matr.fl = 0;
	check_cub_core(str, &matr, var);
	ft_mat_size(&matr.mat[matr.i], &matr);
	var->map.size.y = matr.size.y;
	var->map.mat = get_map_cub(matr.mat, &matr);
	if (ft_char_check(var, 0, x, y))
		flag = printf("\033[1;31mError\n Wrong elements inside map\n\033[0m");
	x = var->s_pos.x;
	y = var->s_pos.y;
	if (!flag && ft_path_check(var, &matr))
		flag = printf("\033[1;31m Check map inside .cub file\n\033[0m");
	if (ft_free_mat(matr.mat) && flag && ft_free_mat(var->map.mat))
		exit(1);
}
