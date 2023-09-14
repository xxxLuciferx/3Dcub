NAME = cub3D

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
					  ft_calloc.c intersections.c\
					  	wall_projection.c intersection_tools.c \
					  	 free.c texturing.c


CFLAGS = -Wall -Wextra -Werror 

OBJ = ${SRC:.c=.o}

all : $(NAME)

$(NAME): $(OBJ)
		cc  -lmlx -framework OpenGL -framework AppKit $(CFLAGS) $^  -o $(NAME)


clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all