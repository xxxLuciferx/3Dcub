/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:47:56 by yichiba           #+#    #+#             */
/*   Updated: 2023/09/06 11:06:49 by yichiba          ###   ########.fr       */
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
    int    row;
    int    column;

    row = p.y;
    while (row < (p.y + height))
    {
        column = p.x;
        while (column < p.x + 1)
        {
            if (column >= 0 && column < tools->lenght && row >= 0 && row < tools->size)
                my_mlx_pixel_put2(&tools->img, column, row, 0xD3D3D3);
            column++;
        }
        row++;
    }
}

void    draw_3d_wall(t_tools *tools, float distance, int i)
{
    t_hit    p;

    p.x = i;
    p.y = ((tools->size / 2) - (((tools->size / 2) * 50) / distance));
    draw_column(tools, p, tools->size - (p.y * 2));
}