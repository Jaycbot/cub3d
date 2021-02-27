NAME = cub3d

SRC_PATH = ./src

SRC = console.c\
		error_handle.c\
		split.c\
		gnl.c\
		gnl_util.c\
		handle_key.c\
		image.c\
		initialize.c\
		main.c\
		maps.c\
		parse_file.c\
		parse_tools.c\
		parse_tools2.c\
		parse_util.c\
		raycast.c\
		raycast2.c\
		utils.c\
		sprite2.c\
		sprite.c\
		save.c

SRCS = $(addprefix $(SRC_PATH)/, $(SRC))

SAVE = screenshot.bmp

OBJS = $(SRCS:.c=.o)

CFLAG = -Wall -Wextra -Wall -fsanitize=address

FRAMEWORK = -framework OpenGL -framework Appkit

HEADER = -I./include

MLX = libmlx.a

LIBPATH = -L./mlx -lmlx

all : $(NAME)

$(NAME)	: $(OBJS) $(MLX)
	gcc -o $(NAME) $(OBJS) $(CFLAG) $(LIBPATH) $(FRAMEWORK)

$(MLX):
	$(MAKE) -C mlx

clean :
	$(MAKE) -C mlx clean
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME) $(SAVE)

re :fclean all

.PHONY: all clean fclean re