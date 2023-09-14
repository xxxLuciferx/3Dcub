/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:47:56 by yichiba           #+#    #+#             */
/*   Updated: 2023/09/14 20:02:32 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put2(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ereas(t_tools *tools)
{
	int	i;
	int	j;

	i = 0;
	while (i < tools->lenght)
	{
		j = 0;
		while (j < tools->size)
		{
			if (j <= tools->size / 2)
				my_mlx_pixel_put2(&tools->img, i, j, \
				tools->pars->ceilling_color);
			else
				my_mlx_pixel_put2(&tools->img, i, j, tools->pars->floor_color);
			j++;
		}
		i++;
	}
}

t_data	*get_texture(t_tools *tools, int i)
{
	float	angle;

	angle = tools->rays[i]->angle;
	if (tools->rays[i]->dir == 'h')
	{
		if (angle >= 0 && angle <= M_PI)
			return (&tools->tex[2]);
		else
			return (&tools->tex[1]);
	}
	else
	{
		if (angle >= M_PI / 2 && angle <= (3 * M_PI) / 2)
			return (&tools->tex[3]);
		else
			return (&tools->tex[0]);
	}
}

void	put_textures(t_tools *tools, int x, t_hit *hit, float start)
{
	float	col;
	float	row;
	float	wall_height;
	float	inc;
	int		i;

	if (tools->rays[x]->dir == 'v')
		col = (int)tools->rays[x]->y % 50;
	else
		col = (int)tools->rays[x]->x % 50;
	wall_height = hit->x - hit->y;
	inc = 50 / wall_height;
	if (start < 0)
		start = 0;
	i = 0;
	row = (inc * start);
	while (i < wall_height && i < tools->size)
	{
		my_mlx_pixel_put2(&tools->img, x, hit->y + i, \
		get_pixel_color_from_image(get_texture(tools, x), row, col));
		row += inc;
		i++;
	}
}

void	draw_texture(t_tools *tools)
{
	t_hit	hit;
	int		x;
	float	wall_height;
	float	start;

	x = 0;
	start = 0;
	while (x < tools->lenght)
	{
		wall_height = 50 * tools->size / (tools->rays[x]->len
				* cos(tools->angle_rad - tools->rays[x]->angle));
		hit.y = (tools->size / 2) - (wall_height / 2);
		hit.x = hit.y + wall_height;
		wall_height = hit.x - hit.y;
		start = (wall_height / 2) - (tools->size / 2);
		if (hit.y > tools->size || hit.y < 0 || hit.x > tools->size
			|| hit.x < 0)
		{
			hit.y = 0;
			hit.x = tools->size + (start * 2);
		}
		put_textures(tools, x, &hit, start);
		x++;
	}
}
