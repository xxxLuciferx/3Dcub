/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 10:06:17 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/17 16:10:27 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_draw(t_tools *tools, int number)
{
	static int counter;
	static int count;

	if(number == 0)
		number = 70;
	while (counter < number)
	{
		count = 0;
		while(count < number)
		{
			mlx_pixel_put(tools->mlx, tools->win, counter, count, 0xFF0000);
			count++;
		}
		counter++;
	}
	// printf("%d, %d", count, counter);
	// exit(0);
}

void	put_map(t_tools *tools)
{
	int i = 0;
	int j = 0;
	static int number;
	while (tools->pars->land[i])
	{
		j = 0;
		while (tools->pars->land[i][j])
		{
			ft_draw(tools, number);
			j++;
			number = number + 50;
		}
		number = 0;
		i++;
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
//-------------------------------------------------------------------

   
	//-----------------------------------------------------------------------
// void	check_next_wall(t_pars *pars, int pos, int line_pos)
// {
// 	printf("IM HERO\n");
// 	if ((pars->land_range / line_pos) >= (pars->land_range / 2 ) && line_pos > 0) // 9AL MEN NESS
// 	{
// 		printf("%d\n", line_pos);
// 		exit(0);
// 		while (line_pos > 0)
// 		{
// 			if (pars->land[line_pos - 1][pos] == '1')
// 				return;
// 			line_pos--;
// 		}
// 		error_map();
// 	}
// 	exit(0);
	// else if (pars->land_range / line_pos <= pars->land_range / 2) // KTAR MEN NESS
	// {
	// 	while (pars->land[line_pos] && line_pos >= 0)
	// 	{
	// 		if(pars->land[line_pos + 1][pos] == '1')
	// 			return;
	// 		line_pos++;
	// 	}
	// 	error_map();
	// }
// }


	//-----------------------------------------------------------------------





// void	if_correct_map(t_pars *pars)
// {
// 	if_player_exist(pars);
// 	// if_valid_lines(pars);
// }


void	initiation(t_tools *tools)
{
	tools->pars->ptr = tools;
	tools->pars->C_B = -1;
	tools->pars->C_G = -1;
	tools->pars->C_B = -1;
	tools->pars->F_R = -1;
	tools->pars->F_G = -1;
	tools->pars->F_B = -1;
	tools->pars->map = NULL;
	tools->pars->north_path = NULL;
	tools->pars->south_path = NULL;
	tools->pars->west_path = NULL;
	tools->pars->east_path = NULL;
	tools->pars->land_range = 0;
	
}
int	biggest_line(t_tools *tools)
{
	int lenght;
	int	i;
	int	j;

	lenght = 0;
	i = 0;
	while (tools->pars->land[i])
	{
		j = 0;
		while (tools->pars->land[i][j])
		{
			j++;
		}
		if(lenght <= j)
			lenght = j;
		i++;
	}
	return(lenght);
}
int main(int argc, char **argv)
{
	t_tools tools;
	
	valid_entry(argc, argv, &tools);
	printf("OK\n");
	// printf("%d\n", tools.pars->land_range);
	tools.mlx = mlx_init();
	tools.win = mlx_new_window(tools.mlx, (biggest_line(&tools) * 50), (50 * tools.pars->land_range + 1), "cub3D");
	// printf("%d, %d\n", tools.player_x, tools.player_y);
	// tools.win = mlx_new_window(tools.mlx, (20 * tools.pars->land_range + 1), (biggest_line(&tools) * 20), "cub3D");
	// exit(1);
	put_map(&tools);
	mlx_key_hook(tools.win, key_codes, &tools);
	mlx_loop(tools.mlx);
}