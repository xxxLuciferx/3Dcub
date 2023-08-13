/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 10:06:17 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/12 18:24:00 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"



// void	put_map(t_tools *tools)
// {
// 	int i = 0;
// 	int j = 0;
// 	while(i <= 10)
// 	{
// 		while(j <= 10)
// 		{
// 			mlx_pixel_put(tools->mlx, tools->win, tools->player_x + i, tools->player_y + j, 0xFFFFFF);
// 			j = j + 1;
// 		}
// 		i++;
// 		j = 0;
// 	}
// 	i = 0;
// 	j = 0;
// 	while(i <= 500)
// 	{
// 		while(j <= 500)
// 		{
// 			mlx_pixel_put(tools->mlx, tools->win, j, i, 0xFF0000);
// 			mlx_pixel_put(tools->mlx, tools->win, i, j, 0xFF0000);
// 			j = j + 50;
// 		}
// 		i++;
// 		j = 0;
// 	}
// }
// int key_codes(int keycode, t_tools *tools)
// {
// 	if (keycode == LEFT)
// 		tools->player_x -= 5;
// 	else if (keycode == RIGHT)
// 		tools->player_x += 5;
// 	else if (keycode == DOWN)
// 		tools->player_y += 5;
// 	else if (keycode == UP)
// 		tools->player_y -= 5;
// 	else if (keycode == ESC)
// 		exit(0);
// 	mlx_clear_window(tools->mlx, tools->win);
// 	put_map(tools);
// 	// mlx_pixel_put(tools->mlx, tools->win, tools->player_x, tools->player_y, 0xFF0000);
// 	return (0);
// }

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
	printf("OK");
}

void	if_valid_lines(char **map)
{
	int i;

	i = 0;
	while (map[i] != 0)
		i++;
	// printf("%d", i);
	first_and_last_line(map[0]);
	first_and_last_line(map[i - 1]);
	while (--i)
	{
		if(map[i][0] != '1')
			error_map();
		if(map[i][ft_strlen(map[i]) - 1] != '1')
			error_map();
	}
	
	exit(0);
	// last_line(map[i]);
}

void	if_valid_map(void)
{
	int fd;
	int i;
	char buffer[1001];
	char **map;
	// i = 0;
	fd = open("test.cub", O_RDONLY, NULL);
	i = read(fd, buffer, 1000);
	buffer[i] = '\0';
	map = ft_split(buffer, '\n');
	if_valid_lines(map);
	
	
	
}
void	valid_entry(int ac, char **av)
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
	if_valid_map();
	exit(0);
}

int main(int argc, char **argv)
{
	// t_tools tools;

	valid_entry(argc, argv);
	// tools.mlx = mlx_init();
	// tools.win = mlx_new_window(tools.mlx, 500, 500, "KHALIL");
	// tools.player_x = 500 / 2;
	// tools.player_y = 500 / 2;
	// put_map(&tools);
	// mlx_key_hook(tools.win, key_codes, &tools);
	// mlx_loop(tools.mlx);
}