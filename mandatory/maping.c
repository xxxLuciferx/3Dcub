/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:33:41 by khaimer           #+#    #+#             */
/*   Updated: 2023/09/14 20:11:15 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_fov(t_tools *tools)
{
	float		angle;
	int			i;
	static int	old;

	i = 0;
	tools->range = (60.0 * M_PI) / RAD;
	orientations(tools);
	angle = (tools->angle_rad - (tools->range / 2));
	ereas(tools);
	while (i < tools->lenght)
	{
		angle = normalize_angle(angle);
		if (old++ == 0)
			tools->rays = creat_rays_table(tools->lenght);
		update_rays(tools->rays[i], angle, intersection(tools, tools->rays[i], \
		angle), i);
		angle += tools->range / (biggest_line(tools) * 50);
		i++;
	}
	draw_texture(tools);
}

void	ft_draw(t_tools *tools, float start_y, float start_x, int color)
{
	float	y;
	float	x;

	y = 0;
	x = 0;
	while (y < 50)
	{
		x = 0;
		while (x < 50)
		{
			my_mlx_pixel_put(&tools->img, start_x + x, start_y + y, color);
			my_mlx_pixel_put(&tools->img, start_x + x, start_y, 0xffd700);
			x++;
		}
		my_mlx_pixel_put(&tools->img, start_x, start_y + y, 0xffd700);
		y++;
	}
}

void	put_player(t_tools *tools)
{
	float	x;
	float	y;
	int		i;
	int		j;

	x = tools->player_x - 5;
	y = tools->player_y - 5;
	i = 0;
	j = 0;
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
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tools->pars->land[i])
	{
		j = 0;
		while (tools->pars->land[i][j])
		{
			if (tools->pars->land[i][j] == '1')
				ft_draw(tools, i * 50, j * 50, GRIS);
			j++;
		}
		i++;
	}
	put_player(tools);
	mlx_put_image_to_window(tools->mlx, tools->win, tools->img.img, 0, 0);
}
