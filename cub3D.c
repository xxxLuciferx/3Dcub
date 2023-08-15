/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 10:06:17 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/15 14:34:13 by khaimer          ###   ########.fr       */
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
//-------------------------------------------------------------------
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
   
	//-----------------------------------------------------------------------
void	check_next_wall(t_pars *pars, int pos, int line_pos)
{
	printf("IM HERO\n");
	if ((pars->land_range / line_pos) >= (pars->land_range / 2 ) && line_pos > 0) // 9AL MEN NESS
	{
		printf("%d\n", line_pos);
		exit(0);
		while (line_pos > 0)
		{
			if (pars->land[line_pos - 1][pos] == '1')
				return;
			line_pos--;
		}
		error_map();
	}
	exit(0);
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
}


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