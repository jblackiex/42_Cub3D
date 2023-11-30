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

bool	check_cub_xpm(t_mat *matr, int i, t_game *var)
{
	int			fd;
	char		*buffer;
	int			flag;
	char		buff;
	static int	xpm;

	flag = 0;
	if (check_extention(&matr->mat[i][matr->j], ".xpm"))
		++flag;
	if (!flag && (split_32(&matr->mat[i][matr->j], &buffer) || !(++flag)))
	{
		fd = open(buffer, O_RDONLY);
		if (fd < 0)
			return (printf("\033[1;31m No .xpm! \n\033[0m"), free(buffer), 1);
		flag = read(fd, &buff, 1);
		close(fd);
		if (flag <= 0)
			return (printf("\033[1;31mError\n .xpm empty\n\033[0m"), 1);
		var->xpm[xpm++] = buffer;
	}
	else if (flag)
		return (printf("\033[1;31mError\n .xpm issue found\n\033[0m"), 1);
	return (0);
}

bool	check_rgb_save(t_mat *m, int j, int bf, int count)
{
	char		*buffer;
	int			flag;
	int			num;
	static int	rgb;

	flag = 0;
	if (rgb == 3 && ++m->k)
		rgb = 0;
	if (!split_32(&m->mat[j][bf--], &buffer))
		return (1);
	m->r = ft_substr(buffer, 0, count);
	count = ft_strlen(m->r);
	while (!flag && m->mat[j][++bf] && m->mat[j][bf] != ',')
		if ((rgb < 2 || count-- > 0) && !ft_isdigit(m->mat[j][bf]))
			flag = 1;
	num = ft_atoi(m->r);
	if (!flag && (num < 0 || num > 255 || !ft_strlen(m->r)))
		++flag;
	else if (!flag && !m->k)
		m->rgb[0].color[rgb++] = num;
	else if (!flag)
		m->rgb[1].color[rgb++] = num;
	if (flag)
		return (free(m->r), free(buffer), 1);
	return (free(m->r), free(buffer), 0);
}

bool	check_rgb_trio(t_mat *matr, int j, int i)
{
	int	flag;
	int	count;
	int	comma;
	int	buff;

	flag = 0;
	comma = 0;
	count = 0;
	while (matr->mat[j][i] && matr->mat[j][0] != ',' && ++i && !flag)
	{
		buff = i;
		while (matr->mat[j][i] && matr->mat[j][i] != ',' && ++count)
			i++;
		if (++comma && (comma < 2 && count > 3))
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

bool	check_cub_rgb(t_mat *m, int *i)
{
	int	f;
	int	t;

	f = 0;
	t = *i + 1;
	m->k = 0;
	if (ft_strncmp(m->mat[*i], "F ", 2) && ++f)
		print_error(0, "F ");
	if (!f && (in_i(m, &t) || ft_strncmp(m->mat[t], "C ", 2)) && ++f)
		print_error(0, "C ");
	++m->fl;
	if (!f && ((in_i(m, i) || check_rgb_trio(m, *i, m->j - 1)
				|| !(++(*i)) || in_i(m, i)) || !(++m->fl) || in_i(m, i)
			|| check_rgb_trio(m, *i, m->j - 1)))
		++f;
	if (f || !(++(*i)) || in_i(m, i))
		return (1);
	m->i = *i;
	return (0);
}

void	check_cub_core(t_mat *matr, t_game *var, t_mat *cub)
{
	int			f;
	static int	i;
	int			tmp;

	f = 0;
	order_map(matr, cub);
	in_i(matr, &i);
	tmp = i;
	if (ft_strncmp(matr->mat[i++], "NO ", 3) && ++f)
		print_error(0, "NO ");
	if (!f && ((in_i(matr, &i) || ft_strncmp(matr->mat[i++], "SO ", 3)) && ++f))
		print_error(0, "SO ");
	if (!f && ((in_i(matr, &i) || ft_strncmp(matr->mat[i++], "WE ", 3)) && ++f))
		print_error(0, "WE ");
	if (!f && ((in_i(matr, &i) || ft_strncmp(matr->mat[i++], "EA ", 3)) && ++f))
		print_error(0, "EA ");
	i = tmp;
	tmp = -1;
	while (!f && ++tmp < 4 && ++matr->fl)
		if (in_i(matr, &i) || check_cub_xpm(matr, i, var) || !(++i)
			|| in_i(matr, &i))
			++f;
	if (((!f && check_cub_rgb(matr, &i)) || f) && ft_free_mat(cub->mat)
		&& ft_free_set(var->xpm, tmp) && ft_free_mat(matr->mat))
		exit (1);
}
