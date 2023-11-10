/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:43:55 by nbordoni          #+#    #+#             */
/*   Updated: 2023/02/12 15:43:58 by nbordoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct s_vector
{
	int	x;
	int	y;
	int	count;
	int	flag;
}		t_vector;

typedef struct s_rgb
{
	int			color[3];
	t_vector	size;
}		t_rgb;

typedef struct s_mat
{
	t_rgb		rgb[2];
	char		**mat;
	int			fd;
	int			k;
	int			j;
	int			i;
	int			fl;
	t_vector	size;
}		t_mat;

typedef struct s_sprites
{
	void		*wall;
	void		*floor;
	void		*coll;
	void		*exit1;
	void		*herow;
	void		*heroa;
	void		*heros;
	void		*herod;
	void		*hero2;
	void		*doorspecial;
	void		*enemy1;
	void		*floorx;
	t_vector	size;
}		t_sprites;

typedef struct s_game
{
	t_mat		map;
	t_vector	s_pos; // prima era hero_pos
	char		orientation;
	char 		*xpm[4];
	int			width;
	int			height;
	float		p_x;
	float		p_y;
	float		fov;
	float		angle;
	float		p_angle;
	void		*mlx;
	void		*win;
}		t_game;


// Parsing Map
void	check_cub_core(char *path, t_mat *matr, t_game *var);
int		in_i(t_mat *matr, int *i);
void	check_core(char *path, t_game *p);
void	print_error(int fd, char *str);
char	**get_map(char *mapy);
bool	check_cub_rgb(t_mat *matr, int *i);
bool	check_extention(char *str, char *doc_cub);
char	**get_map_cub(char **map, t_mat *t);
int		ft_flood_fill(char **tab, t_vector *size, t_vector begin);
int		ft_path_check(t_game *g, t_mat *var);

//Raycasting
void	initializer(t_game *data);
int		handle_keypress(int keycode, t_game *data);
void	move_player(t_game *data, float dx, float dy);
void	rotate_player(t_game *data, float angle);
int		quitter(t_game *data);
int		idle_handler(t_game *data);
void	render(t_game *data);


int		ft_close_game(t_game *g);
int		ft_free_mat(char **mat);

#endif
