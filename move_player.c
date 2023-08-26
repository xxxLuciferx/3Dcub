/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:43:57 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/26 13:48:57 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_tools *tools)
{
	float	coss;
	float	sinn;
	int		y;
	int		x;
	char	**map;

	
	sinn = sin(tools->angle_rad);
	y = tools->player_y;
	x = tools->player_x;
	map = tools->pars->land;
	coss = cos(tools->angle_rad);
	if(map[(int)(((y + 5) + sinn * 10) / 50)][(int)((x + 10 * coss) / 50)] != '1' 
		&& map[(int)(((y - 5) + 10 * sinn) / 50)][(int)((x + 10 * coss) / 50)] != '1'
			&& map[(int)((y + 10 * sinn) / 50)][(int)(((x + 5) + 10 * coss) / 50)] != '1'
				&& map[(int)((y + 10 * sinn) / 50)][(int)(((x - 5) + 10 * coss) / 50)] != '1')
		{
			tools->player_x = x + 10 * coss;
			tools->player_y = y + 10 * sinn;
		}
}

void	move_down(t_tools *tools)
{
	float	coss;
	float	sinn;
	int		y;
	int		x;
	char	**map;

	
	sinn = sin(tools->angle_rad);
	y = tools->player_y;
	x = tools->player_x;
	map = tools->pars->land;
	coss = cos(tools->angle_rad);
	if(map[(int)(((y + 5) - sinn * 10) / 50)][(int)((x - 10 * coss) / 50)] != '1' 
		&& map[(int)(((y - 5) - 10 * sinn) / 50)][(int)((x - 10 * coss) / 50)] != '1'
			&& map[(int)((y - 10 * sinn) / 50)][(int)(((x + 5) - 10 * coss) / 50)] != '1'
				&& map[(int)((y - 10 * sinn) / 50)][(int)(((x - 5) - 10 * coss) / 50)] != '1')
		{
			tools->player_x = x - 10 * (float)coss;
			tools->player_y = y - 10 * (float)sinn;
		}
}

void	move_left(t_tools *tools)
{
	float	coss ;
	float	sinn ;
	int		y;
	int		x;
	char	**map;
	float	angle;

	y = tools->player_y;
	x = tools->player_x;
	map = tools->pars->land;
	angle = M_PI/2 -tools->angle_rad;
	sinn = sin(angle);
	coss = cos(angle);
	if(map[(int)(((y + 5) - sinn * 10) / 50)][(int)((x + 10 * coss) / 50)] != '1' 
		&& map[(int)(((y - 5) - 10 * sinn) / 50)][(int)((x + 10 * coss) / 50)] != '1'
			&& map[(int)((y - 10 * sinn) / 50)][(int)(((x + 5) + 10 * coss) / 50)] != '1'
				&& map[(int)((y - 10 * sinn) / 50)][(int)(((x - 5) + 10 * coss) / 50)] != '1')
	{
		tools->angle_rad = M_PI/2 -tools->angle_rad;
		sinn = sin(tools->angle_rad);
		coss = cos(tools->angle_rad);
		tools->player_x = tools->player_x + 10 * coss;
		tools->player_y = tools->player_y - 10 * sinn;
	}
}
void	move_right(t_tools *tools)
{
	float	coss ;
	float	sinn ;
	int		y;
	int		x;
	char	**map;
	float	angle;

	y = tools->player_y;
	x = tools->player_x;
	map = tools->pars->land;
	angle = M_PI/2 -tools->angle_rad;
	sinn = sin(angle);
	coss = cos(angle);
	if(map[(int)(((y + 5) + sinn * 10) / 50)][(int)((x - 10 * coss) / 50)] != '1' 
		&& map[(int)(((y - 5) + 10 * sinn) / 50)][(int)((x - 10 * coss) / 50)] != '1'
			&& map[(int)((y + 10 * sinn) / 50)][(int)(((x + 5) - 10 * coss) / 50)] != '1'
				&& map[(int)((y + 10 * sinn) / 50)][(int)(((x - 5) - 10 * coss) / 50)] != '1')
	{
		tools->angle_rad = M_PI/2 -tools->angle_rad;
		sinn = sin(tools->angle_rad);
		coss = cos(tools->angle_rad);
		tools->player_x = tools->player_x - 10 * coss;
		tools->player_y = tools->player_y + 10 * sinn;
	}
}

int key_codes(int keycode, t_tools *tools)
{
	if (keycode == CAMERA_LEFT)
		tools->angle -= 10;
	if (keycode == CAMERA_RIGHT)
		tools->angle += 10;
	if (keycode == LEFT )
		move_left(tools);
	else if (keycode == RIGHT)
		move_right(tools);
	else if (keycode == DOWN )
		move_down(tools);
	else if (keycode == UP)
		move_forward(tools);
	else if (keycode == ESC)
		exit(0);
	put_map(tools);
	mlx_put_image_to_window(tools->mlx, tools->win, tools->img.img, 0, 0);
	return (0);
}
