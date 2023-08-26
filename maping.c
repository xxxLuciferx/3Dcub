/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:33:41 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/26 13:35:11 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void draw_fov(t_tools *tools)
{
    float range;
    float start;
    float end;
    float angle;

	range = 60.0;
	start = (tools->angle - (range / 2)) * (PI / RAD);
	end = (tools->angle + (range / 2)) * (PI / RAD);
	angle = start;
    while (angle <= end)
	 {
        draw_direction_line(tools, angle);
        angle += 0.001;
    }
}

void	ft_draw(t_tools *tools, int start_y, int start_x, int red)
{
	(void) red;
	int y = 0;
	int x = 0;
	while (y < 50)
	{
		x = 0;
		while(x < 50)
		{
			my_mlx_pixel_put(&tools->img, start_x + x, start_y + y, red);
			my_mlx_pixel_put(&tools->img, start_x + x, start_y, 0xffd700);
			x++;
		}
			my_mlx_pixel_put(&tools->img, start_x , start_y + y, 0xffd700);
			y++;
	}	
}

void	orientations(t_tools *tools)
{
	float angle = tools->angle * (3.14159265 / 180.0);
	tools->angle_rad = angle;
	tools->x_direction = tools->x_direction * cos(angle);
	tools->y_direction = tools->y_direction * sin(angle);
}

void	put_player(t_tools *tools)
{
	int x = tools->player_x - 5;
	int y = tools->player_y - 5;
	int i = 0;
	int j = 0;
	
	while (i < 10)
	{
		while (j < 10)
		{
			my_mlx_pixel_put(&tools->img, x + i, y + j, 0xFFFFFF);
			j++;
		}
		j = 0;
		i++;
	}
	orientations(tools);
}

void	put_map(t_tools *tools)
{
	int i = 0;
	int j = 0;
	// mlx_clear_window(tools->mlx, tools->win);
	while (tools->pars->land[i])
	{
		j = 0;
		while (tools->pars->land[i][j])
		{
			if(tools->pars->land[i][j] == '1')
				ft_draw(tools, i * 50, j * 50, RED);
			else if(tools->pars->land[i][j] == '0' || tools->pars->land[i][j] == 'N' || tools->pars->land[i][j] == 'S' \
						|| tools->pars->land[i][j] == 'W' || tools->pars->land[i][j] == 'E')
				ft_draw(tools, i * 50, j * 50, BLUE);
			j++;
		}
		i++;
	}
	put_player(tools);
	draw_fov(tools);
	mlx_put_image_to_window(tools->mlx, tools->win, tools->img.img, 0, 0);
	return;
}