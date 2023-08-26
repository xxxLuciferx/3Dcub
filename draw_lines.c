/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:41:21 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/26 13:17:31 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_direction_line(t_tools *tools,float angle)
{
    // int line_length = 350;

    int x;
	int	y;
	int i = 1;
    while(i) 
	{
        x = tools->player_x + i * cos(angle);
        y = tools->player_y + i * sin(angle);
        if(tools->pars->land[y/50][x/50] == '1' || tools->pars->land[y/50][x/50] == '\0' )
        {
            printf("x = %d, y = %d\n", x/50, y/50);
            break;
        }
        my_mlx_pixel_put(&tools->img, x, y, 0x00FF00); // Green color
		i++;
    }
}