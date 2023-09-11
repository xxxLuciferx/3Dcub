/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:47:56 by yichiba           #+#    #+#             */
/*   Updated: 2023/09/11 15:38:18 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	my_mlx_pixel_put2(t_data *data, int x, int y, int color)
{
	char	*dst;
    // x = x/4;
    // y = y/4;
    
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    ereas(t_tools *tools)
{
    int i;
    int j;

    i = 0;
    while (i < tools->lenght)
    {
        j = 0;
        while (j < tools->size)
        {
			if (j <= tools->size/2)
            	my_mlx_pixel_put2(&tools->img, i, j, tools->pars->ceilling_color);
			else
            	my_mlx_pixel_put2(&tools->img, i, j, tools->pars->floor_color);
            j++;
        }
        i++;
    }
}

void draw_column(t_tools *tools, t_hit p, float height)
{
    int     row;
    int     column;
    // int     color;

    row = p.y;
    while (row < (p.y + height))
    {
        column = p.x;
        while (column < p.x + 1)
        {
            if (column >= 0 && column < tools->lenght && row >= 0 && row < tools->size)
                {
                    my_mlx_pixel_put2(&tools->img, column, row, WHITE);
                }
            column++;
        }
        row++;
    }
}


int    get_pixel_colorr(t_tools *tools, t_hit tex,int i)
{
    unsigned int    color;
    
    tools->tex[i].addr = mlx_get_data_addr(&tools->tex[i].img, &tools->tex[i].bits_per_pixel, &tools->tex[i].line_length, &tools->tex[i].endian);
    color = get_pixel_color_from_image(&tools->tex[i], tex.x, tex.y);
    // printf("color = %d\n",color);
    // exit(0);

    return (color);
}

void draw_column_with_texture(t_tools *tools, t_hit p, float height)
{
    int row;
    int column;

    row = p.y;
    float y = 0;
    column = p.x ;
    while (row < (p.y + height))
    {
        if(tools->size  < height)
             p.y = (height / 2) - (tools->size / 2);
        // tex.x = p.x;
        // y = (int) tools->rays[(int)p.x]->y % 50;
        if (column >= 0 && column < tools->lenght && row >= 0 && row < tools->size)
        {
                // my_mlx_pixel_put2(&tools->img, column, row, WHITE);
            // if (column < tools->height && y < tools->height)
                my_mlx_pixel_put2(&tools->img, column, row, get_pixel_color_from_image(&tools->tex[0], (int)column % 50, (int)y% 50));
            // y += (float)tools->rays[(int)p.x]->len / tools->size;
            y +=  tools->height / height ;
        }
        row++;
    }
    // printf("%f\n", y);
}

void    draw_3d_wall(t_tools *tools, float distance, int i)
{
    t_hit    p;
    float wall_height;

    p.x = i;
    distance  = distance * cos(tools->angle_rad - tools->rays[i]->angle);
    wall_height = ((tools->size / 2) - (((tools->size / 2) * 50) / distance));
    draw_column_with_texture(tools, p, tools->size - (p.y * 2));
}
t_data	*get_picture(t_tools *tools, int i)
{
	i = i + 1- 1;
	float angle;
	angle = tools->rays[i]->angle;
	// printf("%f\n", angle);
	if(tools->rays[i]->dir == 'h')
		{
			if(angle >=0 && angle <= M_PI)
				return (&tools->tex[1]);
			else
				return (&tools->tex[2]);
		}
	else
	{
		if(angle >= M_PI / 2 && angle <= (3 * M_PI) / 2)
			return (&tools->tex[0]);
		else
			return (&tools->tex[3]);
	}
}
// t_data	*get_picture(t_tools *tools, int i)
// {
// 	i = i + 1- 1;
// 	float angle;
// 	angle = tools->angle * (M_PI / RAD);
// 	// printf("%f\n", angle);
// 	if ((angle > ((7 * M_PI) / 4) && angle <= M_PI / 4))
// 		return (&tools->tex[0]);
// 	else if (angle > M_PI / 4  && angle <= (3 * M_PI) / 4)
// 		return (&tools->tex[1]);
// 	else if (angle > (3 * M_PI) / 4 && angle <= (5 * M_PI) / 4)
// 		return (&tools->tex[2]);
// 	else if (angle > (5 * M_PI) / 4 && angle <= (7 * M_PI) / 4)
// 		return (&tools->tex[3]);
// 	return (&tools->tex[3]);
// 	// return (NULL);
// }
	
void    put_textures(t_tools *tools,int x, float y0, float y1, float start)
{
    float            col;
    float            row;
    float            wall_height;
    float            inc;
    int                i;

    
    if (tools->rays[x]->dir == 'v')
        col = (int)tools->rays[x]->y % 50;
    else
        col = (int)tools->rays[x]->x % 50;
    wall_height = y1 - y0;
    inc = 50 / wall_height;
    if (start < 0)
        start = 0;
    i = 0;
    row = (inc * start);
    while (i < wall_height && i < tools->size)
    {
        my_mlx_pixel_put2(&tools->img, x,y0 + i, get_pixel_color_from_image(get_picture(tools,x),row,col));
        row += inc;
        i++;
    }
}

void    draw_texture(t_tools *tools)
{
    int        x;
    float       y0;
    float       y1;
    float       distance;
    float       wall_height;
    float       start;

    x = 0;
    start = 0;
    // plot_sky_and_land();
    while (x < tools->lenght)
    {
        // get_y_coordinate(&y0, &y1, distance, g_inf.ray_angle[x]);
        distance  = tools->rays[x]->len * cos(tools->angle_rad - tools->rays[x]->angle);
        wall_height = 50 * tools->size / distance;
        y0 = (tools->size /2) - (wall_height /2);
        y1 = y0 + wall_height;
        wall_height = y1 - y0;
        start = (wall_height / 2) - (tools->size / 2);
        if (y0 > tools->size || y0 < 0 || y1 > tools->size || y1 < 0)
        {
            y0 = 0;
            y1 =tools->size + (start * 2);
        }
        put_textures(tools,x, y0, y1, start);
        x++;
    }
}