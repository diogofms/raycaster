CFLAGS = -g -fsanitize=address -Wall -Wextra -Werror
SRC = ./source/main/main.c ./source/parsing/check_params.c ./source/parsing/parse_map_file.c ./source/parsing/process_textures.c \
		./source/parsing/process_map.c ./source/execution/calculate_rays.c ./source/execution/errors.c ./source/execution/keys.c \
        ./source/execution/movement.c ./source/execution/image.c
OBJ = $(SRC:.c=.o)
NAME = cub3D
MLX_LIB = ./mlx/bulid/libmlx42.a
MLX_DIR = ./mlx42

.PHONY: all clean fclean re libft install

all: libft $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $@ -Iinclude -L"$(MLX_DIR)/build" -lmlx42 -L"/Users/$(USER)/.brew/opt/glfw/lib/" -lglfw -Llibft -lft -framework Cocoa -framework OpenGL -framework IOKit

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

libft:
	make -C libft

install: $(MLX_DIR)
	    cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

$(MLX_DIR):
	if [ ! -d "$(MLX_DIR)" ]; then git clone git@github.com:codam-coding-college/MLX42.git $(MLX_DIR); fi

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

# CFLAGS = -g -Wall -Wextra -Werror
# SRC = ./source/main/main.c ./source/parsing/check_params.c ./source/parsing/parse_map_file.c ./source/parsing/process_textures.c \
# 		./source/parsing/process_map.c ./source/execution/calculate_rays.c ./source/execution/errors.c ./source/execution/keys.c \
#         ./source/execution/movement.c ./source/execution/image.c
# OBJ = $(SRC:.c=.o)
# NAME = cub3D
# MLX_LIB = ./mlx42/build/libmlx42.a
# MLX_DIR = ./mlx42

# .PHONY: all clean fclean re libft install

# all: libft $(NAME)

# $(NAME): $(OBJ)
# 	gcc $(CFLAGS) $(OBJ) -o $@ -L"$(MLX_DIR)/build" -lmlx42 -lglfw -Llibft -lft -lGL -lX11 -lXext -lpthread -lm -ldl

# %.o: %.c
# 	gcc $(CFLAGS) -c $< -o $@

# libft:
# 	make -C libft

# install: $(MLX_DIR)
# 	    cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

# $(MLX_DIR):
# 	if [ ! -d "$(MLX_DIR)" ]; then git clone git@github.com:codam-coding-college/MLX42.git $(MLX_DIR); fi

# clean:
# 	rm -f $(OBJ)
# 	make -C libft clean

# fclean: clean
# 	rm -f $(NAME)
# 	make -C libft fclean

# re: fclean all