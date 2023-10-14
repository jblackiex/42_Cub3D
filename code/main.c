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

// void	*ft_new_window(t_program *p, int widht, int height, char *name)
// {
// 	void	*win;

// 	win = mlx_new_window(p->mlx, widht, height, name);
// 	p->win_size.x = widht;
// 	p->win_size.y = height;
// 	return (win);
// }

// int	ft_close_game(t_game *g)
// {
// 	ft_free_mat(g->map.mat);
// 	ft_free_sprites(g);
// 	mlx_destroy_window(g->game.mlx, g->game.win);
// 	mlx_destroy_display(g->game.mlx);
// 	free(g->game.mlx);
// 	exit(0);
// }

// void	lessgo(t_game *g)
// {
// 	g->w = 48;
// 	g->fire = 0;
// 	g->x1 = 0;
// 	g->x2 = 0;
// 	g->game.mlx = mlx_init();
// 	ft_load_sprites(g);
// 	g->moves = 0;
// 	g->c_cur = 0;
// 	g->game.win = ft_new_window(&g->game,
// 			g->map.size.x * g->sprites.size.x + 0,
// 			g->map.size.y * g->sprites.size.y + 32, "./so_long");
// 	ft_stats(g, 0xFFFFFF);
// 	mlx_hook(g->game.win, 2, 1L << 0, ft_core_keys, g);
// 	mlx_hook(g->game.win, 17, 0, ft_close_game, g);
// 	mlx_loop_hook(g->game.mlx, ft_display_mat, g);
// 	mlx_loop(g->game.mlx);
// }


int	main(int ac, char **av)
{
	t_game	var;

	(void)av;
	if (ac <= 1)
		return (printf("\033[1;31mError\n No argument!\n\033[0m"), 1);
	if (check_extention(av[1], ".cub"))
		return (1);
	check_core(av[1], &var);
	ft_free_mat(var.map.mat);
	printf("YOU DID IT\n");
	//lessgo(&var);
	return (0);
}
