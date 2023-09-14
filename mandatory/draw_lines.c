/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:41:21 by khaimer           #+#    #+#             */
/*   Updated: 2023/09/14 15:13:10 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	x = x / 4;
	y = y / 4;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_color_from_image(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	update_rays(t_ray *ray, float angle, float len_line, int indice)
{
	if (ray->indice == indice)
	{
		ray->angle = angle;
		ray->len = len_line;
	}
}

void	set_angle(t_tools *tools, int keycode)
{
	if (keycode == CAMERA_LEFT)
	{
		tools->angle -= 10;
		tools->angle_rad = tools->angle * (M_PI / RAD);
	}
	else if (keycode == CAMERA_RIGHT)
	{
		tools->angle += 10;
		tools->angle_rad = tools->angle * (M_PI / RAD);
	}
}
