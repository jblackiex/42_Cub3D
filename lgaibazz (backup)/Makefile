NAME = cub3d

LIBFT = libft/libft.a

MINILIBX = minilibx-linux/libmlx.a

SRC =	raycasting.c
	
FLAGS = -no-pie -g #-Wall -Werror -Wextra

LINKS = -lm -lX11 -lXext

all: $(NAME)

$(NAME): libcomp mlxcomp comp

maps:
		@cd maps && ls *.ber -a > list_maps.txt

libcomp:
		@make -C libft

mlxcomp:
		@cd minilibx-linux && ./configure

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
