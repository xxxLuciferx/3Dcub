/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 10:06:17 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/14 19:51:01 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_map(t_tools *tools)
{
	int i = 0;
	int j = 0;
	while(i <= 10)
	{
		while(j <= 10)
		{
			mlx_pixel_put(tools->mlx, tools->win, tools->player_x + i, tools->player_y + j, 0xFFFFFF);
			j = j + 1;
		}
		i++;
		j = 0;
	}
	i = 0;
	j = 0;
	while(i <= 500)
	{
		while(j <= 500)
		{
			mlx_pixel_put(tools->mlx, tools->win, j, i, 0xFF0000);
			mlx_pixel_put(tools->mlx, tools->win, i, j, 0xFF0000);
			j = j + 50;
		}
		i++;
		j = 0;
	}
}
int key_codes(int keycode, t_tools *tools)
{
	if (keycode == LEFT)
		tools->player_x -= 5;
	else if (keycode == RIGHT)
		tools->player_x += 5;
	else if (keycode == DOWN)
		tools->player_y += 5;
	else if (keycode == UP)
		tools->player_y -= 5;
	else if (keycode == ESC)
		exit(1);
	mlx_clear_window(tools->mlx, tools->win);
	put_map(tools);
	// mlx_pixel_put(tools->mlx, tools->win, tools->player_x, tools->player_y, 0xFF0000);
	return (0);
}







void	if_valid_string(char *line)
{
	int	i;
	int	counter;

	i = 1;
	counter = 0;
	while (line[i])
	{
		if(line[i] != ' ' && (line[i] > '9' || line[i] < '0'))
		{
			if(line[i] == ',')
				counter++;
			else
				error_colors();
		}
		i++;
	}
	if(counter != 2)
		error_colors();
}

void	ceiling_colors(t_pars *pars, int i)
{
	char	**tmp;
	
	if_valid_string(pars->map[i]);
	tmp = ft_split(pars->map[i], ",");
	pars->C_R = ft_atoi(tmp[0]);
	pars->C_G = ft_atoi(tmp[1]);
	pars->C_B = ft_atoi(tmp[2]);
	free_arrays(tmp);
	if(pars->C_R < 0 || pars->C_R > 255)
		error_colors();
	if(pars->C_G < 0 || pars->C_G > 255)
		error_colors();
	if(pars->C_B < 0 || pars->C_B > 255)
		error_colors();
}

void	floor_colors(t_pars *pars, int i)
{
	char	**tmp;
	
	if_valid_string(pars->map[i]);
	tmp = ft_split(pars->map[i], ",");
	pars->F_R = ft_atoi(tmp[0]);
	pars->F_G = ft_atoi(tmp[1]);
	pars->F_B = ft_atoi(tmp[2]);
	free_arrays(tmp);
	if(pars->F_R < 0 || pars->F_R > 255)
		error_colors();
	if(pars->F_G < 0 || pars->F_G > 255)
		error_colors();
	if(pars->F_B < 0 || pars->F_B > 255)
		error_colors();
}

void	all_textures(t_pars *pars)
{
	if(!pars->east_path || !pars->north_path || !pars->south_path || !pars->west_path )
		error_path();	
}
void	if_texture(t_pars *pars, int i)
{
	if (pars->map[i][0] == 'C')
		ceiling_colors(pars, i);
	else if (pars->map[i][0] == 'F')
		floor_colors(pars, i);
	else if (pars->map[i][0] == 'N' && pars->map[i][1] == 'O')
		north_path(pars, i);
	else if (pars->map[i][0] == 'S' && pars->map[i][1] == 'O')
		south_path(pars, i);
	else if (pars->map[i][0] == 'W' && pars->map[i][1] == 'E')
		west_path(pars, i);
	else if (pars->map[i][0] == 'E' && pars->map[i][1] == 'A')
		east_path(pars, i);
	
}
int		check_pars(t_pars *pars)
{
	if(pars->east_path == NULL || pars->north_path == NULL || pars->south_path == NULL || pars->west_path == NULL || pars->C_B == -1 || pars->C_G == -1 || pars->C_R == -1 || pars->F_B == -1 || pars->F_G == -1 || pars->F_R == -1)
		return(0);
	return(1);
}
void	if_data_exist(char **map)
{
	int i;
	int j;
	int	data;

	i = 0;
	data = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ' || map[i][j] == '\t')
			j++;
		if(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'F' || map[i][j] == 'C')
			data++;
		i++;
	}
	if(data != 6)
		error_map();
}
void	ft_map_copy(t_pars *pars, int pos)
{
	int	tmp;
	int i;
	
	i = 0;
	while (pars->map[pars->land_range])
		pars->land_range++;
	tmp = pars->land_range - 1;
	pars->land_range = pars->land_range - pos;
	pars->land = malloc(sizeof(char **) * pars->land_range);
	pars->land_range = 0;
	// pars->land[tmp] = ft_strdup(pars->map[pos]);
	// printf("%s\n", pars->land[tmp]);
	while (pars->map[pos])
	{
		pars->land[i] = ft_strdup(pars->map[pos]);
		// printf("%s\n", pars->land[i]);
		pos++;
		i++;
	}
	pars->land_range = i - 1;
}

void	if_line_of_walls(char *line, t_pars *pars)
{
	int i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if(line[i] != '1' && line[i] != ' ')
			error_map();
		i++;
	}
}

void	if_valid_lines(t_pars *pars)
{
	// int i;

	// i = 0;
	if_line_of_walls(pars->land[0], pars);
	if_line_of_walls(pars->land[pars->land_range], pars);
	// if_walls(pars->land[pars->land_range]);
	// printf("%s\n", pars->land[pars->land_range - 1]);
	// if_walls(pars->land[pars->land_range]);
	// printf("%s\n", pars->land[0]);
	// printf("%d\n", pars->land_range);
	// if_walls(map[i - 1]);
	// while (--i)
	// {
	// 	if(map[i][0] != '1')
	// 		error_map();
	// 	if(map[i][ft_strlen(map[i]) - 1] != '1')
	// 		error_map();
	// }
}

void	parsing_data(t_pars *pars)
{
	int i;

	i = 0;
	if_data_exist(pars->map);
	while (pars->map[i])
	{
		if_texture(pars, i);
		if(check_pars(pars))
		{
			i++;
			break;
		}
		i++;
	}
	all_textures(pars);
	ft_map_copy(pars, i);
	if_valid_lines(pars);
	
	printf("IM HERE NOW\n");
}

void	initiation(t_pars *pars)
{
	pars->C_B = -1;
	pars->C_G = -1;
	pars->C_B = -1;
	pars->F_R = -1;
	pars->F_G = -1;
	pars->F_B = -1;
	pars->map = NULL;
	pars->north_path = NULL;
	pars->south_path = NULL;
	pars->west_path = NULL;
	pars->east_path = NULL;
	pars->land_range = 0;
	
}

void	if_valid_map(t_tools *tools)
{
	int fd;
	int i;
	char buffer[1001];
	i = 0;
	
	tools->pars = malloc(sizeof(t_pars));
	initiation(tools->pars);
	fd = open("test.cub", O_RDONLY, NULL);
	i = read(fd, buffer, 1000);
	buffer[i] = '\0';
	tools->pars->map = ft_split(buffer, "\n");

	parsing_data(tools->pars);
	// if_valid_lines(map);  //fixing split
}
void	valid_entry(int ac, char **av, t_tools *tools)
{
	int	len;
	
	if(ac != 2)
	{
		printf("\n$ Invalid arguments\n\n");
		exit(1);
	}
	len = ft_strlen(av[1]);
	if(av[1][len - 1] != 'b' || av[1][len - 2] != 'u' || av[1][len - 3] != 'c' || av[1][len - 4] != '.')
	{
		printf("\n$ Please enter a .cub file\n\n");
		exit(1);
	}
	if_valid_map(tools);
}

int main(int argc, char **argv)
{
	t_tools tools;
	
	valid_entry(argc, argv, &tools);
	exit(1);
	tools.mlx = mlx_init();
	tools.win = mlx_new_window(tools.mlx, 500, 500, "KHALIL");
	tools.player_x = 500 / 2;
	tools.player_y = 500 / 2;
	put_map(&tools);
	mlx_key_hook(tools.win, key_codes, &tools);
	mlx_loop(tools.mlx);
}