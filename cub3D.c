/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 10:06:17 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/25 18:42:03 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"



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




int key_codes(int keycode, t_tools *tools)
{
	int x;
	int y;
	x = (tools->player_x);
	y = (tools->player_y);
	if (keycode == CAMERA_LEFT)
		tools->angle -= 10;
	if (keycode == CAMERA_RIGHT)
		tools->angle += 10;
	if (keycode == LEFT)
	{
		tools->angle_rad = (M_PI / 2) - tools->angle_rad;
		tools->player_x += cos(tools->angle_rad) * 10;
		tools->player_y -= sin(tools->angle_rad) * 10;
	}
	else if (keycode == RIGHT)
	{
		tools->angle_rad = (M_PI / 2) - tools->angle_rad;
		tools->player_x -= cos(tools->angle_rad) * 10 ;
		tools->player_y += sin(tools->angle_rad) * 10 ;
	}
	else if (keycode == DOWN)
	{
		tools->player_x -= cos(tools->angle_rad) * 10 ;
		tools->player_y -= sin(tools->angle_rad) * 10 ;
	}
	else if (keycode == UP)
	{
		tools->player_x += cos(tools->angle_rad) * 10 ;
		tools->player_y += sin(tools->angle_rad) * 10 ;
	}
	else if (keycode == ESC)
		exit(0);
	put_map(tools);
	mlx_put_image_to_window(tools->mlx, tools->win, tools->img.img, 0, 0);
	return (0);
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
void	graphic(t_tools *tools)
{
	tools->mlx = mlx_init();
	tools->win = mlx_new_window(tools->mlx, (biggest_line(tools) * 50), (50 * (tools->pars->land_range + 1)), "cub3D");
	tools->img.img = mlx_new_image(tools->mlx, (biggest_line(tools) * 50), (50 * (tools->pars->land_range + 1)));
	tools->img.addr = mlx_get_data_addr(tools->img.img, &tools->img.bits_per_pixel, &tools->img.line_length, &tools->img.endian);
	tools->player_x = (tools->player_x * 50) + 25;
	tools->player_y = (tools->player_y * 50) + 25;
	put_map(tools);
	mlx_put_image_to_window(tools->mlx, tools->win, tools->img.img, 0, 0);
	mlx_hook(tools->win, 2, 1, key_codes, tools);
	mlx_loop(tools->mlx);
} 
int main(int argc, char **argv)
{
	t_tools tools;
	
	valid_entry(argc, argv, &tools);
	graphic(&tools);
}