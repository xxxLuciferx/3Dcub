NAME = cub3D
# LIBFT = ./libft/libft.a
SRC = cub3D.c  \
		ft_split.c \
		 ft_atoi.c \
		  paths.c \
		   errors.c \
		    leaks.c \
			 ft_map.c \
			  valid_pars.c \
			   ft_walls.c \
			    collect_map.c \
				 maping.c \
				  draw_lines.c\
				  	move_player.c \
					 ft_map_pos.c \
					  ft_calloc.c print.c


CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

OBJ = ${SRC:.c=.o}

# $(LIBFT):
# 	make -C ./libft

all : $(NAME)

$(NAME): $(OBJ)
		cc  -lmlx -framework OpenGL -framework AppKit $(CFLAGS) $^  -o $(NAME)


clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all