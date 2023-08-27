#ifndef cub3D_H
# define cub3D_H

# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>

#define ESC 53
#define LEFT 0
#define RIGHT 2
#define UP 13
#define DOWN 1
#define CAMERA_LEFT 123
#define CAMERA_RIGHT 124
#define RAD 180.0


#define RED	0xFF0000
#define BLUE 0xFF
#define YELLOW 0xFFFFFF


char	**ft_split(char const *s, char *c);
int		ft_atoi(const char *str);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_strtrim(char const *s1, char const *set);



typedef	struct s_pars t_pars;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;



typedef struct	s_tools
{
	t_pars	*pars;
	void	*mlx;
	void	*win;
	int		orientation;
	int 	angle;
	float 	angle_rad;
	int		x_direction;
	int		y_direction;
	int		player_x;
	int		player_y;
	t_data	img;
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
void	reading_map(t_tools *tools, char *av);
void	checking_data(t_pars *pars);
void	if_directions_and_colors_exist(char **map);
int		check_pars(t_pars *pars);


//PARSING MAP (valid_pars.c)
void	collect_texture_and_colors(t_pars *pars, int i);
void	ft_map_copy(t_pars *pars, int pos);
void	if_player_exist(t_pars *pars);
void	if_one_player(t_pars *pars);

// (ft_walls.c)
void	if_valid_inside_lines(t_pars *pars);
void	zero_sides_verification(char **land, int pos_i, int pos_j);
void	left_wall(t_pars *pars);
void	if_line_of_walls(char *line);

// main
void	initiation(t_tools *tools);
void	if_valid_lines(t_pars *pars);
void	if_line_of_walls(char *line);
void	if_valid_string(char *line);
void	check_next_wall(t_pars *pars, int pos, int line_pos);
void	put_map(t_tools *tools);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_direction_line(t_tools *tools,float angle);
int	biggest_line(t_tools *tools);

//(CEILING && FLOOR COLLECTING) (collect_map.c)
void	ceiling_colors(t_pars *pars, int i);
void	floor_colors(t_pars *pars, int i);
void	if_valid_string(char *line);

//maping.c MAP
void	draw_fov(t_tools *tools);
void	ft_draw(t_tools *tools, float start_y, float start_x, int red);
void	orientations(t_tools *tools);
void	put_player(t_tools *tools);
void	put_map(t_tools *tools);
 
 //DRAW LINES
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void 	draw_direction_line(t_tools *tools,float angle);
void	put_player(t_tools *tools);
int    get_pixel_color(t_tools *tools, float x, float y);

//MAP POS (ft_map_pos.c)
void	checking_data(t_pars *pars);
void	map_lines(char *buffer, int pos);
int	first_in_map(char *buffer, int pos);
void	check_new_lines(char *buffer,int start, int end);
int	last_char_pos(char *line, int last_pos);

int key_codes(int keycode, t_tools *tools);
#endif