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
		printf("\033[1;31mError\n Empty .cub or file not found\n\033[0m");
		close(fd);
		exit(1);
	}
	else if (!ft_strncmp(str, ".cub", 4))
		printf("\033[1;31mError\n .cub file must ends with '.cub'\n\033[0m");
	else if (!ft_strncmp(str, ".xpm", 4))
		printf("\033[1;31m .xpm file must ends with '.xpm'\n\033[0m");
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
	print_map(g->map.mat);
	map_flipper(g);
	print_map(g->map.mat);
	render_1(g);
	mlx_hook(g->win, 2, 1L << 0, handle_keypress, g);
	mlx_hook(g->win, 3, 1L << 1, handle_keyrelease, g);
	mlx_hook(g->win, 17, 0, quitter, g);
	mlx_loop_hook(g->mlx, (int (*)(void *))idle_handler, g);
	mlx_loop(g->mlx);
	quitter(g);
}


int	quitter(t_game *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		mlx_destroy_image(data->mlx, data->textures[i].img);
		mlx_destroy_image(data->mlx, data->textures[i].addr);
	}
	// free(data->textures);
	mlx_destroy_window(data->mlx, data->win);
	// free(data->xpm);
	free(data->win);
	free(data->mlx);
	ft_free_mat(data->xpm);
	ft_free_mat(data->map.mat);
	exit(0);
	return (0);
}

//TODO

//file da aggiungere: main, check_matr.c, check_cub.c, utils.c, check_map_utils.c

//texture posizionate correttamente
//scoprire cosa va freeato (ci sono cosa da freeare) --> //valgrind -s --leak-check=full --show-leak-kinds=all ./cub3d maps/minecraft.cub
//norminette


int	main(int ac, char **av)
{
	t_game	var;

	(void)av;
	if (ac <= 1)
		return (printf("\033[1;31mError\n No argument!\n\033[0m"), 1);
	if (check_extention(av[1], ".cub"))
		return (1);
	check_core(av[1], &var);
	// lessgo(&var);
	printf("YOU DID IT\n");
	// ft_free_mat(var.map.mat);
	return (0);
}
