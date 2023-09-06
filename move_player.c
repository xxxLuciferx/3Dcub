/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:43:57 by yichiba           #+#    #+#             */
/*   Updated: 2023/09/06 09:06:41 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		move_forward(t_tools *tools)
{
	float	coss;
	float	sinn;
	float		y;
	float		x;
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
			return(1);
		}
	return(0);
}

int		move_down(t_tools *tools)
{
	float	coss;
	float	sinn;
	float		y;
	float		x;
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
			return(1);
		}
	return(0);
}

int	move_left(t_tools *tools)
{
	float	coss ;
	float	sinn ;
	float		y;
	float		x;
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
		// tools->angle_rad = M_PI/2 - tools->angle_rad;
		// sinn = sin(tools->angle_rad);
		// coss = cos(tools->angle_rad);
		tools->player_x = tools->player_x + 10 * coss;
		tools->player_y = tools->player_y - 10 * sinn;
		return(1);
	}
	return(0);
}
int	move_right(t_tools *tools)
{
	float	coss ;
	float	sinn ;
	float		y;
	float		x;
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
		// tools->angle_rad = M_PI/2 - tools->angle_rad;
		// sinn = sin(tools->angle_rad);
		// coss = cos(tools->angle_rad);
		tools->player_x = tools->player_x - 10 * coss;
		tools->player_y = tools->player_y + 10 * sinn;
		return(1);
		}
	return(0);
}

int key_codes(int keycode, void *ptr)
{
	t_tools *tools = (t_tools *)ptr;
	float angle;
	int ret;
	
	ret  = -1;
	angle = tools->angle;
	if (keycode == CAMERA_LEFT)
		tools->angle -= 10;
	else if (keycode == CAMERA_RIGHT)
		tools->angle += 10;
	else if (keycode == LEFT )
		ret = move_left(tools);
	else if (keycode == RIGHT)
		ret = move_right(tools);
	else if (keycode == DOWN )
		ret = move_down(tools);
	else if (keycode == UP)
		ret = move_forward(tools);
	else if (keycode == ESC)
		exit(0);
	if(ret != 1 && angle == tools->angle)
		return(0);
	draw_fov(tools);
	mlx_put_image_to_window(tools->mlx, tools->win, tools->img.img, 0, 0);
	return (0);
}
