/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:33:41 by khaimer           #+#    #+#             */
/*   Updated: 2023/09/11 18:04:25 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


float	normalize_angle(float angle)
{
	angle = fmodf(angle, 2 * M_PI);
		if(angle < 0)
			angle += 2 * M_PI;
	return(angle);
}

t_ray	**creat_rays_table(int len)
{
	// printf("creat_rays_table\n");
    t_ray** rays;
	int i = 0;
    rays = (t_ray **)malloc(len * sizeof(t_ray *));
    
    if (rays == NULL)
		return NULL;
	while(i < len)
   	{
        rays[i] = ft_lstnew(i);
		i++;
    }
    return rays;
}


void draw_directions(t_tools *tools)
{
	int i = 0;
	put_map(tools);
    while (i < tools->lenght)
	{
		// if(i == tools->lenght/2)
			draw_line_dda(tools, tools->rays[i]->x, tools->rays[i]->y);
		i++;
    }
}
void draw_fov(t_tools *tools)
{
    float 		angle;
	int 		i;
	static	int old;
	
	i = 0;
	tools->range = (60.0 * M_PI)/RAD;
	orientations(tools);
	angle = (tools->angle_rad - (tools->range / 2));
	ereas(tools);
    while (i < tools->lenght)
	{
		angle = normalize_angle(angle);
		if(old++ == 0)
			tools->rays = creat_rays_table(tools->lenght);
		update_rays(tools->rays[i], angle, intersection(tools, tools->rays[i], angle), i);
		// draw_3d_wall(tools, tools->rays[i]->len, i);
	    angle +=tools->range/(biggest_line(tools) *50);
		i++;
    }
		draw_texture(tools);
		draw_directions(tools);
		// print_rays(tools);
}

void	ft_draw(t_tools *tools, float start_y, float start_x, int color)
{
	float y = 0;
	float x = 0;

	while (y < 50)
	{
		x = 0;
		while(x < 50)
		{
			my_mlx_pixel_put(&tools->img, start_x + x, start_y + y, color);
			my_mlx_pixel_put(&tools->img, start_x + x, start_y, 0xffd700);
			x++;
		}
			my_mlx_pixel_put(&tools->img, start_x , start_y + y, 0xffd700);
			y++;
	}
}

void	orientations(t_tools *tools)
{
	float angle;

	angle = tools->angle * (M_PI / RAD);
	tools->angle_rad = angle;
	// tools->x_direction = tools->x_direction * cos(angle);
	// tools->y_direction = tools->y_direction * sin(angle);
}

void	put_player(t_tools *tools)
{
	float x = tools->player_x - 5;
	float y = tools->player_y - 5;
	int i = 0;
	int j = 0;
	
	while (i < 10)
	{
		while (j < 10)
		{
			my_mlx_pixel_put(&tools->img, x + i, y + j, BLACK);
			j++;
		}
		j = 0;
		i++;
	}
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
				ft_draw(tools, i * 50, j * 50, GRis);
			j++;
		}
		i++;
	}
	put_player(tools);
	mlx_put_image_to_window(tools->mlx, tools->win, tools->img.img, 0, 0);
}
