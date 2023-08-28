/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:33:41 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/28 22:44:01 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void draw_fov(t_tools *tools)
{
    float 	range;
    float 	start;
    float 	end;
    float 	angle;
	int		indice;

	indice = 0;
	range = (60.0 * M_PI)/RAD;
	start = (tools->angle_rad - (range / 2));
	end = (tools->angle_rad + (range / 2));
	angle = start;
    while (angle <= end)
	{
        draw_direction_line(tools, angle, indice);
        angle +=range/(biggest_line(tools) *50);
		indice++;
    }
	print_rays(tools->rays);
}

void	my_pixel_put(t_tools *tools, int x, int y, int color)
{
    t_data *data = &tools->img;
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    if(get_pixel_color(tools,x,y) == 0)
		*(unsigned int*)dst = color;
}

void	ft_draw(t_tools *tools, float start_y, float start_x, int color)
{
	float y = 0;
	float x = 0;
		
	while (y < 50)
	{
		x = 0;
		while(x <= 50)
		{
			my_pixel_put(tools, start_x + x, start_y + y, color);
			my_pixel_put(tools, start_x + x, start_y, 0xffd700);
			x++;
		}
			my_pixel_put(tools, start_x , start_y + y, 0xffd700);
			y++;
	}
}

void	orientations(t_tools *tools)
{
	float angle = tools->angle * (M_PI / RAD);
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
			my_mlx_pixel_put(&tools->img, x + i, y + j, YELLOW);
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
	while (tools->pars->land[i])
	{
		j = 0;
		while (tools->pars->land[i][j])
		{
			if(tools->pars->land[i][j] == '1')
				ft_draw(tools, i * 50, j * 50, RED);
			else
				ft_draw(tools, (float)i * 50, (float)j * 50, BLUE);
			j++;
		}
		i++;
	}
	put_player(tools);
	draw_fov(tools);
	mlx_put_image_to_window(tools->mlx, tools->win, tools->img.img, 0, 0);
}