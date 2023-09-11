/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:41:21 by khaimer           #+#    #+#             */
/*   Updated: 2023/09/09 16:42:21 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
    x= x/4;
    y = y/4;
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
    (void) x;
    (void) y;
    
    tools->img.addr = mlx_get_data_addr(tools->img.img, &tools->img.bits_per_pixel, &tools->img.line_length, &tools->img.endian);
    color = get_pixel_color_from_image(&tools->img, 15, 625);
    red = (color >> 16) & 0xFF;
    green = (color >> 8) & 0xFF;
    blue = color & 0xFF;

    // if (red > 150 && green < 100 && blue < 100)
    //         return (1);
    return (color);
}
void    update_rays(t_ray  *ray, float angle, float len_line, int indice)
{
    if(ray->indice == indice)
        {
            ray->angle = angle;
            ray->len = len_line;
        }
}
