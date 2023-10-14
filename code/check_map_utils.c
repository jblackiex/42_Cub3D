#include "Cub3d.h"

// char **get_map_l(char **map, t_mat *t)
// {
// 	int	i;
// 	int k;
// 	int	j;
// 	char **map_real;

// 	i = 0;
// 	k = 0;
// 	map_real = (char **) ft_calloc(t->size.y + 2, sizeof(char *)); // here instead of 9 i should ve set the num of rows
// 	map_real[i] = (char *) ft_memset(ft_calloc(t->size.x + 2, sizeof(char)),
// 		'L', t->size.x + 2);
// 	map_real[t->size.y + 1] = (char *) ft_memset(ft_calloc(t->size.x + 2,
// 		sizeof(char)), 'L', t->size.x + 2);
// 	while (map[i])
// 	{
// 		j = 0;
// 		map_real[++k] = (char *) ft_memset(ft_calloc(t->size.x + 2, sizeof(char)), 'L', t->size.x + 2);
// 		while (++j < t->size.x)
// 			map_real[k][j] = map[i][j - 1];
// 		i++;
// 	}
// 	return (map_real);
// }

int	ft_path_check(t_game *g, t_mat *t)
{
	int	res;
	int	check;
	char **tmp;

	// now i m gonna increase mat dim adding the L character with a function
	// ft_free_mat(t->mat);
	// t->mat = tmp;
	t->size.count = 0;
	res = ft_flood_fill(&t->mat[8], &t->size, g->s_pos);
	// add density check to see number of 1s
	if (t->size.flag == 1)
		printf("\033[1;31mError\n Space character inside the walls\n\033[0m");
	else if (res == 1)
		printf("\033[1;31mError\n 0 on the walls\n\033[0m");
	else if (t->size.count < 10)
		printf("\033[1;31mError\n Too few moves available in game\n\033[0m");	
	return (res);
}

int	ft_free_mat(char **mat)
{
	int	y;

	y = -1;
	while (mat[++y])
		free(mat[y]);
	free(mat);
	return (0);
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