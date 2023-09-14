NAME = cub3D
BONUS = cub3D_bonus

SRC = $(addprefix mandatory/, ft_split.c ft_atoi.c paths.c errors.c leaks.c ft_map.c valid_pars.c ft_walls.c collect_map.c maping.c draw_lines.c move_player.c ft_map_pos.c ft_calloc.c intersections.c wall_projection.c intersection_tools.c free.c texturing.c) \
	cub3D.c
BONUS_SRC = $(addprefix bonus/, ft_split.c ft_atoi.c paths.c errors.c leaks.c ft_map.c valid_pars.c ft_walls.c collect_map.c maping.c draw_lines.c move_player.c ft_map_pos.c ft_calloc.c intersections.c wall_projection.c intersection_tools.c free.c texturing.c) \
	cub3D.c

CFLAGS = -Wall -Wextra -Werror 

OBJ = ${SRC:.c=.o}
BOBJ = ${BONUS_SRC:.c=.o}

all: $(NAME)

bonus: $(BONUS)

$(NAME): $(OBJ)
	cc -lmlx -framework OpenGL -framework AppKit $(CFLAGS) $^ -o $(NAME)

$(BONUS): $(BOBJ)
	cc -lmlx -framework OpenGL -framework AppKit $(CFLAGS) $^ -o $(BONUS)

clean:
	rm -rf $(OBJ) $(BOBJ)

fclean: clean
	rm -rf $(NAME) $(BONUS)

re: fclean all

