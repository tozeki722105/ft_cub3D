# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toshi <toshi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/15 03:56:20 by toshi             #+#    #+#              #
#    Updated: 2024/08/20 10:03:00 by tyamauch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:=	cc -fsanitize=address
# CFLAGS		=	-Wall -Wextra -Werror
RM			:=	rm -rf

NAME		:=	cub3d

OS := $(shell uname -s)

SRCS_DIR = srcs

CALC_DIR = calc

DRAW_DIR = draw

PARSE_DIR = parse

OBJS_DIR = objs

LIBRARY_DIR = library

TESTS_DIR = tests

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

SRCS		:=	$(SRCS_DIR)/$(CALC_DIR)/calc_calc_horizontal_inter_pos.c\
				$(SRCS_DIR)/$(CALC_DIR)/calc_calc_vertical_inter_pos.c\
				$(SRCS_DIR)/$(CALC_DIR)/calc_intersection.c\
				$(SRCS_DIR)/$(CALC_DIR)/calc_utils.c\
				$(SRCS_DIR)/$(CALC_DIR)/calc_utils2.c\
				$(SRCS_DIR)/$(DRAW_DIR)/draw_background.c \
				$(SRCS_DIR)/$(DRAW_DIR)/draw_rect.c \
				$(SRCS_DIR)/$(DRAW_DIR)/draw_utils.c \
				$(SRCS_DIR)/$(DRAW_DIR)/draw_wall.c \
				$(SRCS_DIR)/main.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_add_color.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_load_map_list_to_data.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_load_map_str_to_list.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_load_textures.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_trim_map_list.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_utils_bool.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_utils_free.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_utils_load.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_utils_print.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_validate_map_data_utils.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_validate_map_data.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_utils.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse.c 

PARSE_SRCS	:=	$(SRCS_DIR)/$(PARSE_DIR)/parse_load_utils.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_load_utils2.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_load.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_utils_bool.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_utils_bool2.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_utils_libft.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_utils_libft2.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_utils_map_node.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_utils_map_node2.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_utils.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_validate_map_data_utils.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse_validate_map_data.c \
				$(SRCS_DIR)/$(PARSE_DIR)/parse.c 

OBJS		:=	$(patsubst %.c, ${OBJS_DIR}/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(MLX_PATH)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX_FLAG) -o $(NAME)

${OBJS_DIR}/%.o: %.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

parse: $(PARSE_SRCS)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) $(PARSE_SRCS) $(LIBFT_A)

reparse: clean parse

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test:
	cmake -S . -B $(TESTS_DIR)/build
	cmake --build $(TESTS_DIR)/build
	./$(TESTS_DIR)/build/parse_test

.PHONY:	all clean fclean re test
