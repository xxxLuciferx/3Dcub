/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 10:06:17 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/13 18:01:54 by khaimer          ###   ########.fr       */
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
		exit(0);
	mlx_clear_window(tools->mlx, tools->win);
	put_map(tools);
	// mlx_pixel_put(tools->mlx, tools->win, tools->player_x, tools->player_y, 0xFF0000);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	error_map(void)
{
	printf("\n$ Invalid MAP format\n\n");
	exit(0);
}
void	error_colors(void)
{
	printf("\n$ Invalid MAP colors\n\n");
	exit(0);
}
void	first_and_last_line(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if(line[i] != '1')
			error_map();
		i++;
	}
	// printf("OK");
}

// void	if_valid_lines(char **map)
// {
// 	int i;

// 	i = 0;
// 	while (map[i] != 0)
// 		i++;
// 	first_and_last_line(map[0]);
// 	first_and_last_line(map[i - 1]);
// 	// while (--i)
// 	// {
// 	// 	if(map[i][0] != '1')
// 	// 		error_map();
// 	// 	if(map[i][ft_strlen(map[i]) - 1] != '1')
// 	// 		error_map();
// 	// }
// }
void	free_arrays(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
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
	char **tmp;
	int io = 0;
	
	if_valid_string(pars->map[i]);
	tmp = ft_split(pars->map[i], ',');
	while (tmp[io])
	{
		printf("%s\n", tmp[io]);
		io++;
	}
	// exit(0);
	pars->C_R = ft_atoi(tmp[0]);
	pars->C_G = ft_atoi(tmp[1]);
	pars->C_B = ft_atoi(tmp[2]);
	// printf("====> %d", pars->C_R);
	printf("OOO %d, %d, %d\n", pars->C_R, pars->C_G, pars->C_B);
	exit(0);
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
	char **tmp1;
	// char **tmp2;
	// int io = 0;
	
	if_valid_string(pars->map[i]);
	tmp1 = ft_split(pars->map[i], ',');
	// while (tmp1[io])
	// {
	// 	printf("%s\n", tmp1[io]);
	// 	io++;
	// }
	// tmp2 = ft_split(tmp1[1], ',');
	pars->F_R = ft_atoi(tmp1[0]);
	pars->F_G = ft_atoi(tmp1[1]);
	pars->F_B = ft_atoi(tmp1[2]);
	printf("%d, %d, %d\n", pars->F_R, pars->F_G, pars->F_B);
	exit(0);
	free_arrays(tmp1);
	// free_arrays(tmp2);
	if(pars->F_R < 0 || pars->F_R > 255)
		error_colors();
	if(pars->F_G < 0 || pars->F_G > 255)
		error_colors();
	if(pars->F_B < 0 || pars->F_B > 255)
		error_colors();
}
void	parsing_data(t_pars *pars)
{
	int i;

	i = 0;
	while (pars->map[i])
	{
		
		if (pars->map && pars->map[i][0] == 'C' && pars->map[i][1] == ' ')
			ceiling_colors(pars, i);
		else if (pars->map[i][0] == 'F' && pars->map[i][1] == ' ')
			floor_colors(pars, i);
		i++;
	}
	printf("OKAY\n");
	exit(0);
	// printf("celing => %d, %d, %d, \n", pars->C_B, pars->C_G, pars->C_R);
	// printf("floor => %d, %d, %d, ", pars->F_B, pars->F_G, pars->F_R);
	
	
	
}

void	if_valid_map(t_tools *tools)
{
	int fd;
	int i;
	char buffer[1001];
	i = 0;
	
	tools->pars = malloc(sizeof(t_pars));
	fd = open("test.cub", O_RDONLY, NULL);
	i = read(fd, buffer, 1000);
	buffer[i] = '\0';
	tools->pars->map = ft_split(buffer, '\n');
	
	// printf("%s", tools->pars->map[11]);

	parsing_data(tools->pars);
	// if_valid_lines(map);  //fixing split
}
void	valid_entry(int ac, char **av, t_tools *tools)
{
	int	len;
	
	if(ac != 2)
	{
		printf("\n$ Invalid arguments\n\n");
		exit(0);
	}
	len = ft_strlen(av[1]);
	if(av[1][len - 1] != 'b' || av[1][len - 2] != 'u' || av[1][len - 3] != 'c' || av[1][len - 4] != '.')
	{
		printf("\n$ Please enter a .cub file\n\n");
		exit(0);
	}
	if_valid_map(tools);
}

int main(int argc, char **argv)
{
	t_tools tools;

	valid_entry(argc, argv, &tools);
	tools.mlx = mlx_init();
	tools.win = mlx_new_window(tools.mlx, 500, 500, "KHALIL");
	tools.player_x = 500 / 2;
	tools.player_y = 500 / 2;
	put_map(&tools);
	mlx_key_hook(tools.win, key_codes, &tools);
	mlx_loop(tools.mlx);
}