NAME = cub3D
# LIBFT = ./libft/libft.a
SRC = cub3D.c ft_split.c ft_atoi.c paths.c errors.c leaks.c ft_map.c valid_pars.c ft_walls.c collect_map.c
CFLAGS = -Wall -Wextra -Werror

OBJ = ${SRC:.c=.o}

# $(LIBFT):
# 	make -C ./libft

all : $(NAME)

$(NAME): $(OBJ)
		cc $(CFLAGS) $^  -o $(NAME)

# -lmlx -framework OpenGL -framework AppKit


clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all