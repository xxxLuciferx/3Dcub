/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:33:41 by khaimer           #+#    #+#             */
/*   Updated: 2023/09/04 15:01:17 by yichiba          ###   ########.fr       */
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
	printf("creat_rays_table\n");
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


void draw_fov(t_tools *tools)
{
    float 	angle;
	int 	i;
	static	int old;

	tools->range = (60.0 * M_PI)/RAD;
	angle = (tools->angle_rad - (tools->range / 2));
	i = 0;
		system("clear");
    while (i < 2)
	{angle = normalize_angle(angle);
		if(old++ == 0)
			tools->rays = creat_rays_table(2);
		update_rays(tools->rays[i], angle, intersection(tools, tools->rays[i], angle), i);
		draw_line_dda(tools, tools->rays[i]->x, tools->rays[i]->y);
        angle +=tools->range/(biggest_line(tools) *50);
		
		i++;
    }
		print_rays(tools);
}

// void draw_fov(t_tools *tools)
// {
//     float 	angle;
// 	float	x;
// 	float	y;
// 	int 	i;
// 	static	int old = 0;

// 	tools->range = (60.0 * M_PI)/RAD;
// 	angle = (tools->angle_rad - (tools->range / 2));
// 	i = 0;
//     while (i < tools->lenght)
// 	{
// 		angle = normalize_angle(angle);
// 		if(old++ <= i)
// 			ft_lstadd_back(&tools->rays, ft_lstnew(tools, angle, intersection(tools, &x, &y,angle), i));
// 		else
// 			update_rays(tools, angle, intersection(tools, &x, &y,angle), i);
// 		draw_line_dda(tools, x,y);
//         angle +=tools->range/(biggest_line(tools) *50);
// 		// break;
// 		i++;
//     }
// 	print_rays(tools->rays);
// 	// exit(0);
// }

// void draw_fov(t_tools *tools)
// {
//     float 	angle;
// 	float	x;
// 	float	y;
// 	int 	i;
// 	static	int old = 0;
// 	int len = 0;

// 	tools->range = (60.0 * M_PI)/RAD;
// 	angle = (tools->angle_rad - (tools->range / 2));
// 	i = 0;
//     while (i < tools->lenght)
// 	{
// 		angle = normalize_angle(angle);
// 		len = intersection(tools, &x, &y,angle);
// 		if(old <= i)
// 		{
// 			ft_lstadd_back(&tools->rays, ft_lstnew(tools, angle, len, i));
// 			old++;
// 			printf("create them\n");
// 		}
// 		else
// 		{
// 			printf("update\n");
// 			update_rays(tools, angle, len, i);
// 		}
// 		draw_line_dda(tools, x,y);
//         angle +=tools->range/(biggest_line(tools) *50);
// 		// break;
// 		i++;
//     }
// 	// print_rays(tools->rays);
// 	// exit(0);
// }

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
		while(x < 50)
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
	float x = tools->player_x - 5;
	float y = tools->player_y - 5;
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
			else if(tools->pars->land[i][j] != ' ')
				ft_draw(tools, (float)i * 50, (float)j * 50, BLUE);
			j++;
		}
		i++;
	}
	put_player(tools);
	draw_fov(tools);
	mlx_put_image_to_window(tools->mlx, tools->win, tools->img.img, 0, 0);
}
