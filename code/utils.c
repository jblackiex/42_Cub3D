/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:42:35 by nbordoni          #+#    #+#             */
/*   Updated: 2023/02/12 15:42:37 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Cub3d.h"

void	initializer(t_game *data)
{
	data->width = 600;
	data->height = 400;
	data->fov = 35 * (M_PI / 180);
	if (data->orientation == 'N')
		data->p_angle = M_PI;
	else if (data->orientation == 'E')
		data->p_angle = 1.5 * M_PI;
	else if (data->orientation == 'S')
		data->p_angle = 0;
	else if (data->orientation == 'W')
		data->p_angle = 0.5 * M_PI;
	data->move_up = 0;
	data->move_down = 0;
	data->move_left = 0;
	data->move_right = 0;
	data->turn_left = 0;
	data->turn_right = 0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "Cub3D");
	data->textures[0] = load_texture(data->mlx, data->xpm[0]);
	data->textures[1] = load_texture(data->mlx, data->xpm[1]);
	data->textures[2] = load_texture(data->mlx, data->xpm[2]);
	data->textures[3] = load_texture(data->mlx, data->xpm[3]);
}

void	ft_find_init(int *zero, int *one, int *space, int *other)
{
	*zero = 0;
	*one = 0;
	*space = 0;
	*other = 0;
}

static int	ft_find_str(char *str)
{
	int	i;
	int	zero;
	int	one;
	int	space;
	int	other;

	i = 0;
	ft_find_init(&zero, &one, &space, &other);
	while (str[i])
	{
		if (str[i] == '0')
			zero++;
		else if (str[i] == '1')
			one++;
		else if (str[i] == ' ' || str[i] == '	')
			space++;
		else
			other++;
		i++;
	}
	if (!other && ((zero > 0 && one > 0) || (zero > 0 && space > 0)
			|| (one > 0 && space > 0)) || (one > 0 && !space && !zero)
		|| (zero > 0 && !space && !one))
		return (1);
	return (0);
}

int	not_set(char *c, char **set, int flag)
{
	int	i;

	i = -1;
	if (flag)
	{
		set[0] = ft_strdup("NO ");
		set[1] = ft_strdup("SO ");
		set[2] = ft_strdup("WE ");
		set[3] = ft_strdup("EA ");
		set[4] = ft_strdup("F ");
		set[5] = ft_strdup("C ");
		set[6] = "\0";
		return (0);
	}
	while (set[++i])
	{
		if (set[i][0] == '\0')
			break ;
		if ((i < 4 && !ft_strncmp(set[i], c, 2))
			|| (i >= 4 && !ft_strncmp(set[i], c, 1)))
			return (0);
	}
	return (1);
}

int	order_map(t_mat *tmp, t_mat *matr)
{
	int			i;
	static int	j;
	char		*set[7];

	i = -1;
	not_set(matr->mat[0], set, 1);
	tmp->mat = (char **) ft_calloc(matr->size.y + 2, sizeof(char *));
	while (matr->mat[++i])
	{
		if (j < 6 && in_order(&matr->mat[i][0], set, j, matr))
		{
			if (i < 6 || (!ft_find_str(matr->mat[i - 1])
					&& (matr->mat[i + 1] && !ft_find_str(matr->mat[i + 1]))))
			{
				tmp->mat[j++] = ft_strdup(matr->buff);
				i = -1;
			}
		}
		else if (j > 5 && in_order(&matr->mat[i][0], set, -1, matr) ||
				(i > 5 && (ft_find_str(matr->mat[i - 1])
				|| (matr->mat[i + 1] && ft_find_str(matr->mat[i + 1])))))
			tmp->mat[j++] = ft_strdup(matr->mat[i]);
	}
	return (ft_free_set(set, 6), tmp->mat[j] = NULL, 0);
}
