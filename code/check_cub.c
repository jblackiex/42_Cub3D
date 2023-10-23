#include "Cub3d.h"

bool	check_cub_xpm(t_mat *matr, int i, t_game *var)
{
	int			fd;
	int			flag;
	char		buff;
	static int	xpm;

	flag = 0;
	if (check_extention(&matr->mat[i][matr->j], ".xpm"))
		++flag;
	if (!flag)
	{
		fd = open(&matr->mat[i][matr->j], O_RDONLY);
		if (fd < 0 && close(fd))
			return (printf("\033[1;31mError\n .xpm not found\n\033[0m"), 1);
		flag = read(fd, &buff, 1);
		close(fd);
		if (flag <= 0)
			return (printf("\033[1;31mError\n .xpm empty\n\033[0m"), 1);
		var->xpm[xpm++] = ft_strdup(&matr->mat[i][matr->j]); // da freeare
	}
	else if (flag)
		return (1);
	return (0);
}


bool	check_rgb_save(t_mat *matr, int j, int buff, int count)
{
	char		*buffer;
	int			flag;
	int			num;
	static int	rgb;

	flag = 0;
	if (rgb == 3 && ++matr->k)
		rgb = 0;
	buffer = ft_substr(&matr->mat[j][buff], 0, count);
	if (--buff && !buffer)
		return (1);
	while(!flag && matr->mat[j][++buff] && matr->mat[j][buff] != ',')
		if (!ft_isdigit(matr->mat[j][buff]))
			flag = 1;
	num = ft_atoi(buffer);
	if (!flag && (num < 0 || num > 255))
		++flag;
	else if (!flag)
		if (!matr->k)
			matr->rgb[0].color[rgb++] = num; // F
		else
			matr->rgb[1].color[rgb++] = num; // C
	if (flag)
		return (free(buffer), 1);
	return (free(buffer), 0);
}

bool	check_rgb_trio(t_mat *matr, int j, int i)
{
	int	flag;
	int	count;
	int	comma;
	int buff;

	flag = 0;
	comma = 0;
	count = 0;
	while (matr->mat[j][i] && matr->mat[j][0] != ',' && ++i && !flag)
	{
		buff = i;
		while (matr->mat[j][i] && matr->mat[j][i] != ',' && ++count)
			i++;
		if (++comma && count > 3)
			++flag;
		if (comma > 3 || (matr->mat[j][buff] == '0'
			&& (matr->mat[j][buff + 1] && matr->mat[j][buff + 1] != ',')))
			++flag;
		if (!flag && check_rgb_save(matr, j, buff, count))
			++flag;
		count = 0;
	}
	if (flag || comma != 3 || matr->mat[j][--i] == ',')
		return (print_error(0, " Check RGB options inside .cub file"), 1);
	return (0);
}

bool	check_cub_rgb(t_mat *matr, int *i)
{
	int	f;
	int	tmp;

	f = 0;
	tmp = *i + 1;
	matr->k = 0;
	if (ft_strncmp(matr->mat[*i], "F ", 2) && ++f)
		print_error(0, "F ");
	if ((in_i(matr, &tmp) || ft_strncmp(matr->mat[tmp], "C ", 2)) && ++f)
		print_error(0, "C ");
	++matr->fl;
	if (!f && ((in_i(matr, i) || check_rgb_trio(matr, *i, matr->j - 1)
	|| !(++(*i)) || in_i(matr, i)) || !(++matr->fl) || in_i(matr, i)
	|| check_rgb_trio(matr, *i, matr->j - 1)))
		++f;
	if (f || !(++(*i)) || in_i(matr, i))
		return (1);
	matr->i = *i;
	return (0);
}

//se ho problemi close fd in caso di errori. Vedere file matr_bonus
void check_cub_core(char *path, t_mat *matr, t_game *var)
{
	int	f;
	int	i;
	int	tmp;

	f = 0;
	i = 0;
	matr->mat = get_map(path);
	in_i(matr, &i);
	tmp = i;
	if (ft_strncmp(matr->mat[i++], "NO ", 3) && ++f)
		print_error(0, "NO ");
	if ((in_i(matr, &i) || ft_strncmp(matr->mat[i++], "SO ", 3)) && ++f)
		print_error(0, "SO ");
	if ((in_i(matr, &i) || ft_strncmp(matr->mat[i++], "WE ", 3)) && ++f)
		print_error(0, "WE ");
	if ((in_i(matr, &i) || ft_strncmp(matr->mat[i++], "EA ", 3)) && ++f)
		print_error(0, "EA ");
	i = tmp;
	tmp = -1;
	while (!f && ++tmp < 4 && ++matr->fl)
		if (in_i(matr, &i) || check_cub_xpm(matr, i, var) || !(++i)
			|| in_i(matr, &i))
			++f;
	if (((!f && check_cub_rgb(matr, &i)) || f) && ft_free_mat(matr->mat))
		exit (1);
}