#include "Cub3d.h"

bool	check_cub_xpm(t_mat *matr, int i)
{
	int	fd;
	int	flag;
	char *buff;

	flag = 0;
	buff = 0;
	if (check_extention(&matr->mat[i][3], ".xpm"))
		++flag;
	if (!flag)
	{
		fd = open(&matr->mat[i][3], O_RDONLY); // forse queste me le devo salvare
		if (fd < 0 && ++flag)
			printf("\033[1;31mError\n .xpm file not found\n\033[0m");
		else
		{
			buff = get_next_line(fd); //instead of buff i should ve used a struct variable
			close (fd); // i ll do it later --> matr->xpm[i] = &matr->mat[i][3];
			if (!buff)
				return (printf("\033[1;31mError\n .xpm empty\n\033[0m"), 1);
			free(buff);
		}
	}
	if (flag)
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
	if (j == 6 && rgb == 2)
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
		if (j == 5)
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
	while (matr->mat[j][i] && matr->mat[j][2] != ',' && ++i && !flag)
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

bool	check_cub_rgb(t_mat *matr)
{
	int	flag;

	flag = 0;
	if (ft_strncmp(matr->mat[5], "F ", 2) && ++flag)
		print_error(0, "F ");
	if (ft_strncmp(matr->mat[6], "C ", 2) && ++flag)
		print_error(0, "C ");
	if (!flag && (check_rgb_trio(matr, 5, 1) || check_rgb_trio(matr, 6, 1)))
		++flag;
	if (flag)
		return (1);
	return (0);
}

//se ho problemi close fd in caso di errori. Vedere file matr_bonus
void check_cub_core(char *path, t_mat *matr)
{
	int	flag;
	int	i;

	flag = 0;
	i = -1;
	matr->mat = get_map(path);
	// printf("matr->mat[0] = %s\n", matr->mat[0]);
	// printf("matr->mat[1] = %s\n", matr->mat[1]);
	if (ft_strncmp(matr->mat[0], "NO ", 3) && ++flag)
		print_error(0, "NO ");
	if (ft_strncmp(matr->mat[1], "SO ", 3) && ++flag)
		print_error(0, "SO ");
	if (ft_strncmp(matr->mat[2], "WE ", 3) && ++flag)
		print_error(0, "WE ");
	if (ft_strncmp(matr->mat[3], "EA ", 3) && ++flag)
		print_error(0, "EA ");
	while (!flag && ++i < 4)
		if (check_cub_xpm(matr, i))
			++flag;
	if (!flag && check_cub_rgb(matr))
		++flag;
	if (flag)
	{
		ft_free_mat(matr->mat);
		exit(1);
	}
}