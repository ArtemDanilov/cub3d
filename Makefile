CC = cc

FLAGS = -Wall -Wextra -Werror

NAME = cub3D

LIBMLX = libmlx.a
LIBMLX_DIRNAME = minilibx
LIBFT = libft.a
LIBFT_DIRNAME = libft
OBJ_DIR = ./obj
RESOURCES_DIR = ./resources

ROOT_FILE = main
RESOURCES = gnl parsing_file

CFILES = $(ROOT_FILE:%=%.c) $(RESOURCES:%=$(RESOURCES_DIR)/%.c)
OBJ = $(CFILES:%.c=$(OBJ_DIR)/%.o)

MLX_FLAGS = -L/usr/lib -lXext -lX11 -lm -lz -o
MLX_OBJ_FLAGS = -I/usr/include -Imlx_linux -O3

all: $(OBJ_DIR) $(NAME)

$(LIBMLX_DIRNAME)/$(LIBMLX):
	$(MAKE) -C $(LIBMLX_DIRNAME)

$(NAME): $(OBJ) $(LIBMLX_DIRNAME)/$(LIBMLX) $(LIBFT_DIRNAME)/$(LIBFT)
	$(CC) $(OBJ) -L./$(LIBMLX_DIRNAME) -lmlx -L./$(LIBFT_DIRNAME) -lft $(MLX_FLAGS) $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(MLX_OBJ_FLAGS) -c $< -o $@

$(LIBFT_DIRNAME)/$(LIBFT):
	$(MAKE) -C $(LIBFT_DIRNAME)

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ) $(OBJ_DIR)
	$(MAKE) -C $(LIBMLX_DIRNAME) clean
	$(MAKE) -C $(LIBFT_DIRNAME) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIRNAME) fclean

re: fclean all

.PHONY: all, clean, fclean, re 