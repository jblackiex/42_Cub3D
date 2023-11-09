/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:43:49 by nbordoni          #+#    #+#             */
/*   Updated: 2023/02/12 15:43:51 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Cub3d.h"

void	print_error(int fd, char *str)
{
	if (!str)
	{
		printf("\033[1;31mError\n Empty .cub, file not found\n\033[0m");
		close(fd);
		exit(1);
	}
	else if (!ft_strncmp(str, ".cub", 4))
		printf("\033[1;31mError\n .cub file must ends with '.cub'\n\033[0m");
	else if (!ft_strncmp(str, ".xpm", 4))
		printf("\033[1;31m .xpm file must ends with '.xpm'\n\033[0m");
	else if (!ft_strncmp(str, "NO ", 3))
		printf("\033[1;31mError\n .cub line 1 must start with 'NO '\n\033[0m");
	else if (!ft_strncmp(str, "SO ", 3))
		printf("\033[1;31mError\n .cub line 2 must start with 'SO '\n\033[0m");
	else if (!ft_strncmp(str, "WE ", 3))
		printf("\033[1;31mError\n .cub line 3 must start with 'WE '\n\033[0m");
	else if (!ft_strncmp(str, "EA ", 3))
		printf("\033[1;31mError\n .cub line 4 must start with 'EA '\n\033[0m");
	else if (!ft_strncmp(str, "C ", 2))
		printf("\033[1;31mError\n .cub line 7 must start with 'C '\n\033[0m");
	else if (!ft_strncmp(str, "F ", 2))
		printf("\033[1;31mError\n .cub line 6 must start with 'F '\n\033[0m");
	else
		printf("\033[1;31mError\n%s\n\033[0m", str);
}

void	*ft_new_window(t_program *p, int widht, int height, char *name)
{
	void	*win;

	win = mlx_new_window(p->mlx, widht, height, name);
	p->win_size.x = widht;
	p->win_size.y = height;
	return (win);
}

int	ft_close_game(t_game *g)
{
	ft_free_mat(g->xpm);
	ft_free_mat(g->map.mat);
	// ft_free_sprites(g);
	mlx_destroy_window(g->game.mlx, g->game.win);
	mlx_destroy_display(g->game.mlx);
	free(g->game.mlx);
	exit(0);
}

void	lessgo(t_game *g)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	initializer(data);
	data->p_x = (float)g->s_pos.x + 0.5;
	data->p_y = (float)g->s_pos.y + 0.5;
	data->map = g->map.mat;
	render(data);
	// mlx_do_key_autorepeaton(data->mlx);
	mlx_hook(data->win, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win, 17, 0, quitter, data);
	mlx_loop_hook(data->mlx, (int (*)(void *))idle_handler, data);
	mlx_loop(data->mlx);
	quitter(data);
}

int	main(int ac, char **av)
{
	t_game	var;

	(void)av;
	if (ac <= 1)
		return (printf("\033[1;31mError\n No argument!\n\033[0m"), 1);
	if (check_extention(av[1], ".cub"))
		return (1);
	check_core(av[1], &var);
	lessgo(&var);
	printf("YOU DID IT\n");
	// ft_free_mat(var.map.mat);
	return (0);
}
