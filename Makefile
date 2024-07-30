# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshi <toshi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/15 03:56:20 by toshi             #+#    #+#              #
#    Updated: 2024/07/31 02:35:02 by toshi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:=	cc
# CFLAGS		=	-Wall -Wextra -Werror
RM			:=	rm -rf

NAME		:=	cub3d

OS := $(shell uname -s)

SRCS_DIR = srcs/

OBJS_DIR = objs

LIBRARY_DIR = library

DIR_DUP = mkdir -p $(@D)

ifeq ($(OS),Linux)
	MLX_PATH    :=  $(LIBRARY_DIR)/minilibx-linux/
	MLX_FLAG    := -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lbsd
else
	MLX_PATH	:=	$(LIBRARY_DIR)/minilibx_opengl_20191021/
	MLX_FLAG	:=	-L$(MLX_PATH) -l mlx -framework OpenGL -framework AppKit
endif

LIBFT_PATH	:=	$(LIBRARY_DIR)/libft/
LIBFT_A		:=	$(LIBFT_PATH)libft.a

GNL_PATH	:=	$(LIBRARY_DIR)/gnl/

INCLUDES_DIR = includes
INCLUDES = -I$(INCLUDES_DIR) -I$(MLX_PATH) -I$(LIBFT_PATH) -I$(GNL_PATH)

SRCS		:=	$(SRCS_DIR)ogv1.c \
				$(SRCS_DIR)calc_intersection.c \
				$(SRCS_DIR)draw_wall.c \
				$(SRCS_DIR)utils_calc.c \
				$(SRCS_DIR)utils_draw.c \
				$(SRCS_DIR)calc_inter.c \
				$(SRCS_DIR)calc_inter_horizon.c \

OBJS		:=	$(patsubst %.c, ${OBJS_DIR}/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(MLX_PATH)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAG) -o $(NAME)

${OBJS_DIR}/%.o: %.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
