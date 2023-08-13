#ifndef cub3D_H
# define cub3D_H

# include <unistd.h>
# include <stdio.h>
// # include <mlx.h>
#include <stdlib.h>
#include <fcntl.h>

#define ESC 53
#define LEFT 123
#define RIGHT 124
#define UP 126
#define DOWN 125

char	**ft_split(char const *s, char c);

typedef struct	s_tools
{
	void	*mlx;
	void	*win;
	int		player_x;
	int		player_y;
}				t_tools;


#endif