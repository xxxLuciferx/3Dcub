/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:47:56 by yichiba           #+#    #+#             */
/*   Updated: 2023/09/11 08:28:01 by yichiba          ###   ########.fr       */
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
            my_mlx_pixel_put2(&tools->img, i, j, 0x000000);
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
        my_mlx_pixel_put2(&tools->img, x,y0+i, get_pixel_color_from_image(&tools->tex[1],row,col));
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