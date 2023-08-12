NAME = cub3D
# LIBFT = ./libft/libft.a
SRC = cub3D.c
CFLAGS = -Wall -Wextra -Werror

OBJ = ${SRC:.c=.o}

# $(LIBFT):
# 	make -C ./libft

all : $(NAME)

$(NAME): $(OBJ)
		cc $(CFLAGS) $^ -lmlx -framework OpenGL -framework AppKit -o $(NAME)


clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all