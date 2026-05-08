CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR) -I./resources/raycaster -I./libft
LIBS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -L./libft -lft

MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_REPO = https://github.com/42Paris/minilibx-linux.git

LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_REPO = https://github.com/ArtemDanilov/Libft.git

TARGET = raycaster
SRC = resources/raycaster/raycaster_2d.c \
      resources/raycaster/raycaster_3d.c \
      resources/raycaster/raycaster_utils.c \
      resources/parsing/parsing.c \
      resources/parsing/map.c \
      resources/parsing/textures.c \
      resources/parsing/utilities.c \
      resources/parsing/free_mem.c \
      resources/gnl.c

all: $(LIBFT_LIB) $(MLX_LIB) $(TARGET)

$(LIBFT_LIB):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Cloning Libft..."; \
		git clone $(LIBFT_REPO) $(LIBFT_DIR); \
	fi
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MiniLibX..."; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	@if [ ! -f "$@" ]; then \
		echo "Building MiniLibX..."; \
		$(MAKE) -C $(MLX_DIR); \
	fi

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(MLX_LIB) $(LIBS)

clean:
	rm -f $(TARGET)
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR) clean; fi

fclean: clean
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR) fclean; fi

re: fclean all
