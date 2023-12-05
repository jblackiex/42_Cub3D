NAME = cub3D

LIBFT = libft/libft.a

MINILIBX = minilibx-linuxx/libmlx.a

SRC =	code/main.c \
	code/floodfill.c \
	code/check_cub.c \
	code/utils.c \
	code/check_matr.c \
	code/check_map_utils.c \
	code/matr.c \
	code/movement.c \
	code/raycasting.c \
	code/raycasting_utils.c \
	code/utils2.c \
	
FLAGS = -no-pie -g -Wall -Werror -Wextra

LINKS = -lm -lX11 -lXext

all: $(NAME)

$(NAME): libcomp mlxcomp comp

maps:
		@cd maps && ls *.cub -a > list_maps.txt

libcomp:
		@make -C libft

mlxcomp:
		@cd minilibx-linuxx && ./configure

comp:
	gcc $(FLAGS) $(SRC) $(MINILIBX) $(LIBFT) $(LINKS) -o $(NAME)

libclean:
		@make clean -C libft 

clean:		libclean

libfclean:
		@make fclean -C libft

fclean:   	clean libfclean
		rm -rf $(NAME) $(NAME2)
		rm -rf maps/list_maps.txt
		
re: fclean all

reb: fclean

.PHONY: all re clean fclean maps

.SILENT:
