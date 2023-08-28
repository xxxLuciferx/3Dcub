/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:41:21 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/28 15:47:41 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
int get_pixel_color_from_image(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}
int    get_pixel_color(t_tools *tools, float x, float y)
{
    unsigned int    color;
    unsigned char red ;
    unsigned char green;
    unsigned char blue;

    
    tools->img.addr = mlx_get_data_addr(tools->img.img, &tools->img.bits_per_pixel, &tools->img.line_length, &tools->img.endian);
    color = get_pixel_color_from_image(&tools->img, x, y);
    red = (color >> 16) & 0xFF;
    green = (color >> 8) & 0xFF;
    blue = color & 0xFF;

    if (red > 150 && green < 100 && blue < 100)
            return (1);
    return (0);
}


void draw_direction_line(t_tools *tools,float angle, int indice)
{
    float x;
	float	y;
	int len_line;

    len_line = 0;    
    while(1) 
	{
        x = tools->player_x + len_line * cos(angle);
        y = tools->player_y + len_line * sin(angle);
        if(get_pixel_color(tools, x, y) == 1)
        {
            ft_lstadd_back(&tools->rays, ft_lstnew(tools, angle, len_line, indice));
            break;
        }
        my_mlx_pixel_put(&tools->img, x, y, 0x00FF00);
		len_line++;
    }
    
}
