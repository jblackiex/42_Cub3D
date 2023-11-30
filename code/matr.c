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

int	ft_free_ptr(void **ptr, int fd)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	if (fd > 0)
		print_error(fd, NULL);
	return (1);
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
	old_address = "test";
	while (1)
	{
		holder = get_next_line(fd);
		if (!holder)
			break ;
		old_address = map;
		map = ft_strjoin(old_address, holder);
		ft_free_ptr((void *)&old_address, -1);
		ft_free_ptr((void *)&holder, -1);
	}
	if (old_address)
		ft_free_ptr((void *)&map, fd);
	result = ft_split_mod(map, '\n');
	return (close(fd), ft_free_ptr((void *)&map, -1), result);
}

int	split_32(char *str, char **buffer)
{
	int	i;
	int	tmp;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '	')
		i++;
	tmp = i;
	while (str[tmp])
	{
		if (str[tmp] != ' ' && str[tmp] != '	')
			return (0);
		tmp++;
	}
	*buffer = ft_substr(str, 0, i);
	if (!(*buffer))
		return (0);
	return (1);
}

int	in_order(char *str, char **set, int j, t_mat *matr)
{
	char	*tmp;
	int		i;

	tmp = str;
	i = 0;
	while (*tmp && (*tmp == ' ' || *tmp == '	') && ++i)
		tmp++;
	if (j == -1)
		return (not_set(tmp, set, 0));
	if (!ft_strncmp(set[j], tmp, 2))
		return (matr->buff = tmp, 1);
	return (0);
}

int	ft_free_set(char **mat, int dim)
{
	int	y;

	y = -1;
	while (++y < dim)
		free(mat[y]);
	return (1);
}
