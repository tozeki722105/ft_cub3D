# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshi <toshi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/15 03:56:20 by toshi             #+#    #+#              #
#    Updated: 2024/07/15 17:09:28 by tyamauch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:=	cc
# CFLAGS		=	-Wall -Wextra -Werror
RM			:=	rm -rf

NAME		:=	cub3d

OS := $(shell uname -s)

OBJS_DIR = objs

DIR_DUP = mkdir -p $(@D)

ifeq ($(OS),Linux)
	MLX_PATH    :=  ./minilibx-linux/
	MLX_FLAG    := -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lbsd
else
	MLX_PATH	:=	./minilibx_opengl_20191021/
	MLX_FLAG	:=	-L$(MLX_PATH) -l mlx -framework OpenGL -framework AppKit
endif

LIBFT_PATH	:=	libft/
LIBFT_A		:=	$(LIBFT_PATH)libft.a

SRCS		:=	ogv1.c \
				calc_intersection.c \
				draw_wall.c \
				utils_calc.c \
				utils_draw.c

OBJS		:=	$(patsubst %.c, ${OBJS_DIR}/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(MLX_PATH)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAG) -o $(NAME)

${OBJS_DIR}/%.o: %.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
