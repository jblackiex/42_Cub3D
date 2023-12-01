/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:42:59 by nbordoni          #+#    #+#             */
/*   Updated: 2023/02/12 15:43:03 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Cub3d.h"

int	in_i(t_mat *matr, int *i)
{
	int	j;

	j = 0;
	while (matr->mat[*i] && &matr->mat[*i][j] && matr->mat[*i][j])
	{
		if (matr->fl)
			j = 2;
		while (&(matr->mat[*i][j]) && (matr->mat[*i][j] == ' '
			|| matr->mat[*i][j] == '	'))
			j++;
		if (matr->mat[*i][j] && (&matr->mat[*i][j]) && matr->mat[*i][j] == '\n')
			while (!matr->fl && matr->mat[*i] && matr->mat[*i][0] == '\n')
				*i += 1;
		if (matr->mat[*i] && (!matr->mat[*i][j] || (matr->mat[*i][j] != ' '
			&& matr->mat[*i][j] != '	')))
		{
			matr->j = j;
			break ;
		}
		j = 0;
	}
	return (matr->fl = 0, 0);
}

int	ft_path_check(t_game *g, t_mat *t)
{
	int	res;

	t->size.count = 0;
	t->size.flag = 0;
	res = ft_flood_fill(&t->mat[t->i], &t->size, g->s_pos);
	if (t->size.flag == 1)
		printf("\033[1;31mError\n Map is not surrounded by walls\n\033[0m");
	else if (t->size.count < 10)
		res = printf("\033[1;31mError\n Too few moves available\n\033[0m");
	return (res);
}

int	ft_free_mat(char **mat)
{
	int	y;

	y = 0;
	while (mat[y])
		free(mat[y++]);
	free(mat);
	return (1);
}

char	*point_xpm(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] == ' ' || str[i] == '	')
		i--;
	if (str[i] == 'm' && ft_strncmp(&str[i - 4], ".xpm", 4))
		i -= 3;
	return (&str[i]);
}

bool	check_extention(char *str, char *doc_cub)
{
	char	*buffer;

	if (!ft_strncmp(doc_cub, ".cub", 4))
	{
		if (ft_strncmp(&str[ft_strlen(str) - 4], doc_cub, 4)
			|| str[ft_strlen(str) - 1] != 'b')
			return (print_error(0, ".cub"), 1);
	}
	else if (!ft_strncmp(doc_cub, ".xpm", 4))
	{
		buffer = point_xpm(str);
		if (ft_strncmp(buffer, doc_cub, 4))
			return (print_error(0, ".xpm"), 1);
	}
	return (0);
}
