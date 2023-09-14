/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:26:27 by khaimer           #+#    #+#             */
/*   Updated: 2023/09/14 19:04:25 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define HEIGHT 50
# define WIDTH 50

# define ESC 53
# define LEFT 0
# define RIGHT 2
# define UP 13
# define DOWN 1
# define CAMERA_LEFT 123
# define CAMERA_RIGHT 124
# define RAD 180.0
# define MAC_PX 2550
# define MAC_PY 1400
# define READER 30000
# define VERTICAL 0
# define HORIZENTAL 1

# define SQ_SIZE 50

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define GRIS 0x808080
# define RED 0xFF0000
# define BLUE 0xFF
# define YELLOW 0xFFFFFF

char					**ft_split(char const *s, char *c);
int						ft_atoi(const char *str);
char					*ft_strdup(const char *s1);
size_t					ft_strlen(const char *s);
int						ft_strcmp(char *s1, char *s2);

typedef struct s_hit
{
	float				x;
	float				y;
}						t_hit;

typedef struct s_pars	t_pars;

typedef struct s_data
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_data;

typedef struct s_ray
{
	int					indice;
	float				x;
	float				y;
	float				angle;
	float				len;
	char				dir;
}						t_ray;

typedef struct s_tools
{
	t_ray				**rays;
	t_pars				*pars;
	void				*mlx;
	void				*win;
	int					angle;
	float				angle_rad;
	float				player_x;
	float				player_y;
	float				size;
	float				lenght;
	float				range;
	t_data				img;
	t_data				tex[4];
	int					width;
	int					height;

}						t_tools;

typedef struct s_pars
{
	unsigned int		ceilling_color;
	unsigned int		floor_color;

	int					c_r;
	int					c_g;
	int					c_b;
	int					f_r;
	int					f_g;
	int					f_b;
	char				**map;
	char				**land;
	int					land_range;
	char				*north_path;
	char				*south_path;
	char				*west_path;
	char				*east_path;
	t_tools				*ptr;

}						t_pars;

void					north_path(t_pars *pars, int i);
void					south_path(t_pars *pars, int i);
void					west_path(t_pars *pars, int i);
void					east_path(t_pars *pars, int i);
void					file_not_found(t_tools *tools);
void					error_map(void);
void					error_colors(t_pars *pars);
void					error_path(void);
int						close_window(void *param);
void					error_player(t_tools *tools);
void					error_file(t_tools *tools);
void					free_arrays(char **array);
void					valid_entry(int ac, char **av, t_tools *tools);
void					reading_map(t_tools *tools, char *av);
void					checking_data(t_pars *pars);
void					if_directions_and_colors_exist(t_pars *pars);
int						check_pars(t_pars *pars);
void					collect_texture_and_colors(t_pars *pars, int i);
void					ft_map_copy(t_pars *pars, int pos);
void					if_player_exist(t_pars *pars);
void					if_one_player(t_pars *pars);
void					if_valid_inside_lines(t_pars *pars);
void					zero_sides_verification(t_pars *pars, int pos_i,
							int pos_j);
void					left_wall(t_pars *pars);
void					collect_direction(char c, t_pars *pars);
char					*ft_strddup(const char *s1, int len);
void					if_line_of_walls(t_pars *pars, char *land);
void					initiation(t_tools *tools);
void					if_valid_lines(t_pars *pars);
void					check_next_wall(t_pars *pars, int pos, int line_pos);
void					put_map(t_tools *tools);
void					my_mlx_pixel_put(t_data *data, int x, int y, int color);
void					draw_direction_line(t_tools *tools, float angle,
							int indice);
int						biggest_line(t_tools *tools);
void					free_map(char **land);
unsigned int			ceiling_colors(t_pars *pars, int i);
unsigned int			floor_colors(t_pars *pars, int i);
void					draw_fov(t_tools *tools);
void					ft_draw(t_tools *tools, float start_y, float start_x,
							int red);
void					orientations(t_tools *tools);
void					put_player(t_tools *tools);
void					put_map(t_tools *tools);
void					my_mlx_pixel_put(t_data *data, int x, int y, int color);
void					put_player(t_tools *tools);
int						get_pixel_color(t_tools *tools, float x, float y);
void					checking_data(t_pars *pars);
void					map_lines(char *buffer, int pos);
int						first_in_map(char *buffer, int pos);
void					check_new_lines(t_tools *tools, char *buffer, int start,
							int end);
int						last_char_pos(t_tools *tools, char *line, int last_pos);
void					*ft_calloc(size_t count, size_t size);
void					ft_lstadd_back(t_ray **lst, t_ray *new);
t_ray					*ft_lstnew(int indice);
void					print_rays(t_tools *tools);
int						key_codes(int keycode, void *ptr);
float					intersection(t_tools *tools, t_ray *ray, float angle);
int						intersection_horiz(t_tools *tools, t_hit *h,
							float angle, int i);
int						intersection_verti(t_tools *tools, t_hit *v,
							float angle, int i);
void					draw_line_dda(t_tools *tools, float x2, float y2);
void					update_rays(t_ray *ray, float angle, float len_line,
							int indice);
void					draw_column(t_tools *tools, t_hit p, float height);
void					draw_3d_wall(t_tools *tools, float distance, int i);
void					ereas(t_tools *tools);
int						get_pixel_color_from_image(t_data *data, int x, int y);
void					draw_texture(t_tools *tools);
t_ray					**creat_rays_table(int len);
float					normalize_angle(float angle);
void					draw_directions(t_tools *tools);
float					ray_lenght(t_tools *tools, float x2, float y2);
float					absolutevalue(double num);
void					set_angle(t_tools *tools, int keycode);
void					set_angle(t_tools *tools, int keycode);
void					free_all(t_tools *tools);

#endif