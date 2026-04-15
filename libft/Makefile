CC = cc

FLAGS = -Wall -Wextra -Werror

NAME = libft.a

FILES = atoi itoa bzero calloc split \
		tolower toupper \
		isalnum isalpha isascii isdigit isprint \
		memchr memcmp memcpy memmove memset \
		strchr strdup strjoin strlcat strlcpy strlen strncmp strnstr strrchr strtrim substr

CFILES = $(FILES:%=ft_%.c)
OBJ = $(FILES:%=ft_%.o)

$(NAME):
	$(CC) $(FLAGS) -c $(CFILES) -I./
	ar -r $(NAME) $(OBJ)

all: $(NAME)

# Only for tests..........
test:
	$(CC) $(FLAGS) test_func.c $(CFILES) -o test_func.out -lbsd

test-additional:
	$(CC) $(FLAGS) test_additional_func.c $(CFILES) -o test_additional_func.out -lbsd
# ........................

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
