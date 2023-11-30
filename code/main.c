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

void	print_error(int fd, char *str)
{
	if (!str)
	{
		printf("\033[1;31mError\n Empty .cub or file not found\n\033[0m");
		close(fd);
		exit(1);
	}
	else if (!ft_strncmp(str, ".cub", 4))
		printf("\033[1;31mError\n .cub file must ends with '.cub'\n\033[0m");
	else if (!ft_strncmp(str, ".xpm", 4))
		printf("\033[1;31m .xpm line must ends with '.xpm'\n\033[0m");
	else if (!ft_strncmp(str, "NO ", 3))
		printf("\033[1;31mError\n .cub line 'NO ' is the problem\n\033[0m");
	else if (!ft_strncmp(str, "SO ", 3))
		printf("\033[1;31mError\n .cub line 'SO ' is the problem\n\033[0m");
	else if (!ft_strncmp(str, "WE ", 3))
		printf("\033[1;31mError\n .cub line 'WE ' is the problem\n\033[0m");
	else if (!ft_strncmp(str, "EA ", 3))
		printf("\033[1;31mError\n .cub line 'EA ' is the problem\n\033[0m");
	else if (!ft_strncmp(str, "C ", 2))
		printf("\033[1;31mError\n .cub line 'C ' is the problem\n\033[0m");
	else if (!ft_strncmp(str, "F ", 2))
		printf("\033[1;31mError\n .cub line 'F ' is the problem\n\033[0m");
	else
		printf("\033[1;31mError\n%s\n\033[0m", str);
}

void	lessgo(t_game *g)
{
	initializer(g);
	map_flipper(g);
	render_1(g);
	mlx_hook(g->win, 2, 1L << 0, handle_keypress, g);
	mlx_hook(g->win, 3, 1L << 1, handle_keyrelease, g);
	mlx_hook(g->win, 17, 0, quitter, g);
	mlx_loop_hook(g->mlx, (int (*)(void *))idle_handler, g);
	mlx_loop(g->mlx);
}

void	*ft_free_null(char **read)
{
	if (!*read)
		return (NULL);
	free(*read);
	*read = NULL;
	return (NULL);
}

int	quitter(t_game *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (data->textures[i].img)
			mlx_destroy_image(data->mlx, data->textures[i].img);
	}
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	ft_free_null((char **) &data->mlx);
	ft_free_set(data->xpm, 4);
	ft_free_mat(data->map.mat);
	exit(0);
}

int	main(int ac, char **av)
{
	t_game	var;

	(void)av;
	if (ac != 2)
		return (printf("\033[1;31mError\n Wrong arguments!\n\033[0m"), 1);
	if (check_extention(av[1], ".cub"))
		return (1);
	check_core(av[1], &var);
	lessgo(&var);
	return (0);
}
