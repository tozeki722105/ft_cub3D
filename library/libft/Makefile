CC		:=	cc
AR		:=	ar rcs
RM		:=	rm -f

CFLAGS	:=	-Wall -Wextra -Werror

NAME	:=	libft.a

SRCS	:=	ft_isalpha.c\
			ft_isdigit.c\
			ft_isalnum.c\
			ft_isascii.c\
			ft_isprint.c\
			ft_strlen.c\
			ft_memset.c\
			ft_bzero.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_strlcpy.c\
			ft_strlcat.c\
			ft_toupper.c\
			ft_tolower.c\
			ft_strchr.c\
			ft_strrchr.c\
			ft_strncmp.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_strnstr.c\
			ft_atoi.c\
			ft_calloc.c\
			ft_strdup.c\
			ft_substr.c\
			ft_strjoin.c\
			ft_strtrim.c\
			ft_split.c\
			ft_itoa.c\
			ft_strmapi.c\
			ft_striteri.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			get_next_line.c \
			get_next_line_utils.c \
			ft_itonbase.c \
			ft_strncmp.c \
			ft_count_rows.c \
			ft_double_str_dup.c \
			ft_free_double_str.c \
			ft_isequal.c \
			ft_my_perror_ret_false.c \
			ft_strtrim_sepasets.c \
			ft_validate_extention.c \
			ft_can_open.c \
			ft_my_perror_exit.c \
			ft_x_calloc.c \
			ft_x_double_str_dup.c \
			ft_x_itoa.c \
			ft_x_malloc.c \
			ft_x_realloc.c \
			ft_x_split.c \
			ft_x_strdup.c \
			ft_x_strjoin.c \
			ft_x_strtrim_sepasets.c \
			ft_x_strtrim.c \
			ft_x_substr.c \
			ft_perror_exit.c 

OBJS		:=	$(patsubst %.c, %.o, $(SRCS))

.PHONY:	all clean fclean re debug

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: main.o $(OBJS)
	$(CC) $^ -o main.exe
