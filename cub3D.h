#ifndef cub3D_H
# define cub3D_H

# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
#include <stdlib.h>
#include <fcntl.h>

#define ESC 53
#define LEFT 123
#define RIGHT 124
#define UP 126
#define DOWN 125

char	**ft_split(char const *s, char *c);
int		ft_atoi(const char *str);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);

typedef	struct s_pars t_pars;


typedef struct	s_tools
{
	t_pars	*pars;
	void	*mlx;
	void	*win;
	int		player_x;
	int		player_y;
}				t_tools;

typedef	struct s_pars
{
	int		C_R;
	int		C_G;
	int		C_B;

	int		F_R;
	int		F_G;
	int		F_B;

	char	**map;
	char	**land;
	int		land_range;

	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;

	t_tools	*ptr;

}				t_pars;

//PATH FUNCTIONS (paths.c)
void	north_path(t_pars *pars, int i);
void	south_path(t_pars *pars, int i);
void	west_path(t_pars *pars, int i);
void	east_path(t_pars *pars, int i);

//ERRORS (errors.c)
void	error_map(void);
void	error_colors(void);
void	error_path(void);
void	if_all_textures_exist(t_pars *pars);
void	error_player(void);

//LEAKS (leaks.c)
void	free_arrays(char **array);

//MAP (ft_map.c)
void	valid_entry(int ac, char **av, t_tools *tools);
void	reading_map(t_tools *tools);
void	checking_data(t_pars *pars);
void	if_directions_and_colors_exist(char **map);
int		check_pars(t_pars *pars);


//PARSING MAP (valid_pars.c)
void	collect_texture_and_colors(t_pars *pars, int i);
void	ft_map_copy(t_pars *pars, int pos);
void	if_player_exist(t_pars *pars);

// (ft_walls.c)
void	ft_surrounded_walls(t_pars *pars);

// main
void	initiation(t_tools *tools);
void	if_valid_lines(t_pars *pars);
void	if_line_of_walls(char *line, t_pars *pars, int line_pos);
void	floor_colors(t_pars *pars, int i);
void	ceiling_colors(t_pars *pars, int i);
void	if_valid_string(char *line);
void	check_next_wall(t_pars *pars, int pos, int line_pos);

//(CEILING && FLOOR COLLECTING) (collect_map.c)
void		ceiling_colors(t_pars *pars, int i);
void	floor_colors(t_pars *pars, int i);
#endif