NAME = cub3D
# LIBFT = ./libft/libft.a
SRC = cub3D.c ft_split.c
CFLAGS = -Wall -Wextra -Werror

OBJ = ${SRC:.c=.o}

# $(LIBFT):
# 	make -C ./libft

all : $(NAME)

$(NAME): $(OBJ)
		cc $(CFLAGS) $^ -o $(NAME)


clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all