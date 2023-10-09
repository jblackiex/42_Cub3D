# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbordoni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/12 15:12:17 by nbordoni          #+#    #+#              #
#    Updated: 2023/02/12 15:12:20 by nbordoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC = gcc

NAME = libft.a

SRC :=	libft/ft_atoi.c\
	libft/ft_bzero.c\
	libft/ft_calloc.c\
	libft/ft_isalnum.c\
	libft/ft_isalpha.c \
	libft/ft_isascii.c\
	libft/ft_isdigit.c\
	libft/ft_isprint.c\
	libft/ft_itoa.c\
	libft/ft_memchr.c\
	libft/ft_memcmp.c\
	libft/ft_memcpy.c\
	libft/ft_memmove.c\
	libft/ft_memset.c\
	libft/ft_putchar_fd.c\
	libft/ft_putendl_fd.c\
	libft/ft_putnbr_fd.c\
	libft/ft_putstr_fd.c\
	libft/ft_split.c\
	libft/ft_strchr.c\
	libft/ft_strdup.c\
	libft/ft_strjoin.c\
	libft/ft_strlcat.c\
	libft/ft_strlcpy.c\
	libft/ft_strlen.c\
	libft/ft_strmapi.c\
	libft/ft_strncmp.c\
	libft/ft_strnstr.c\
	libft/ft_strrchr.c\
	libft/ft_substr.c\
	libft/ft_tolower.c\
	libft/ft_toupper.c\
	libft/ft_striteri.c\
	libft/ft_split.c\
	libft/ft_strtrim.c

PTF := ft_printf/ft_functions.c\
	ft_printf/ft_printf.c\
	ft_printf/ft_putnbr_base.c\

GNL :=	get_next_line/get_next_line_bonus.c\


BNS :=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
	ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJ_S = $(SRC:.c=.o) $(GNL:.c=.o) $(PTF:.c=.o)

OBJ_B = $(BNS:.c=.o) $(GNL:.c=.o) $(PTF:.c=.o)

CFLAG = -Wall -Werror -Wextra

all: $(NAME) status

$(NAME): $(OBJ_S)
	ar -rcs $@ $^ 


%.o:%.c
	@$(CC) -c $(CFLAG) -I. $< -o $@
status:
	echo "\033[5;1;92mcompleted\033[0m"
clean: status
	/bin/rm -f libft/*.o
	/bin/rm -f ft_printf/*.o
	/bin/rm -f get_next_line/*.o

fclean:	clean
	/bin/rm -f $(NAME)

re: fclean all


bonus: $(OBJ_B)
	ar -rcs $(NAME) $^

.PHONY: all clean fclean re bonus
.SILENT:
