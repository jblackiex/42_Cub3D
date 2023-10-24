NAME = cub3d
NAME2 = cub3d

LIBFT = libft/libft.a

MINILIBX = minilibx-linux/libmlx.a

SRC =	code/main.c \
	code/floodfill.c \
	code/check_cub.c \
	code/utils.c \
	code/check_matr.c \
	code/check_map_utils.c \
	code/matr.c \
	code/imgs.c \
	code/keys.c \

BNS = ##
	
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
	
bonus: libcomp mlxcomp maps
	gcc $(FLAGS) $(BNS) $(MINILIBX) $(LIBFT) $(LINKS) -o $(NAME2)
            
libclean:
		@make clean -C libft
		
clean:		libclean

libfclean:
		@make fclean -C libft

fclean:   	clean libfclean
		rm -rf $(NAME) $(NAME2)
		rm -rf maps/list_maps.txt
		
re: fclean all

reb: fclean bonus

.PHONY: all re clean fclean bonus maps

.SILENT:
