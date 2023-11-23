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
			|| matr->mat[*i][j] == '\t'))
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
	if (!matr->mat[*i] || !(&matr->mat[*i][j]) || (!matr->fl && j && *i < 6
		&& (matr->mat[*i][j - 1] == ' ' || matr->mat[*i][j - 1] == '	')))
		return (printf("\033[1;31mError\n bad .cub file\n\033[0m"), 1);
	return (matr->fl = 0, 0);
}

int	ft_path_check(t_game *g, t_mat *t)
{
	int	res;

	t->size.count = 0;
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

bool	check_extention(char *str, char *doc_cub)
{
	if (!ft_strncmp(doc_cub, ".cub", 4))
	{
		if (ft_strncmp(&str[ft_strlen(str) - 4], doc_cub, 4)
			|| str[ft_strlen(str) - 1] != 'b')
			return (print_error(0, ".cub"), 1);
	}
	else if (!ft_strncmp(doc_cub, ".xpm", 4))
	{
		if (ft_strncmp(&str[ft_strlen(str) - 4], doc_cub, 4)
			|| str[ft_strlen(str) - 1] != 'm')
			return (print_error(0, ".xpm"), 1);
	}
	return (0);
}
