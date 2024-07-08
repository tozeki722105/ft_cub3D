# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshi <toshi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/15 03:56:20 by toshi             #+#    #+#              #
#    Updated: 2024/07/03 14:10:19 by toshi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:=	cc
# CFLAGS		=	-Wall -Wextra -Werror
RM			:=	rm -f

NAME		:=	cub3d

MLX_PATH	:=	./minilibx_opengl_20191021/
MLX_FLAG	:=	-L$(MLX_PATH) -l mlx -framework OpenGL -framework AppKit

LIBFT_PATH	:=	libft/
LIBFT_A		:=	$(LIBFT_PATH)libft.a

SRCS		:=	ogv1.c
OBJS		:=	$(patsubst %.c, %.o, $(SRCS))


all: $(NAME)

$(NAME): $(OBJS)
	make -C $(MLX_PATH)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAG) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re