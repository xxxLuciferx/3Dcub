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

}				t_pars;
typedef struct	s_tools
{
	t_pars	*pars;
	void	*mlx;
	void	*win;
	int		player_x;
	int		player_y;
}				t_tools;

//PATH FUNCTIONS (paths.c)
void	north_path(t_pars *pars, int i);
void	south_path(t_pars *pars, int i);
void	west_path(t_pars *pars, int i);
void	east_path(t_pars *pars, int i);

//ERRORS (errors.c)
void	error_map(void);
void	error_colors(void);
void	error_path(void);

//LEAKS (leaks.c)
void	free_arrays(char **array);

#endif