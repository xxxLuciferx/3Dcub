/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:26:22 by yichiba           #+#    #+#             */
/*   Updated: 2023/09/14 14:27:34 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	ray_lenght(t_tools *tools, float x2, float y2)
{
	float	distance;
	float	dist;
	double	dx;
	double	dy;

	distance = 0;
	dist = 0;
	dx = x2 - tools->player_x;
	dy = y2 - tools->player_y;
	distance = sqrt(dx * dx + dy * dy);
	dist = absolutevalue(distance);
	return (dist);
}

float	absolutevalue(double num)
{
	if (num == INT_MIN)
		return (-(num + 3));
	else if (num < 0)
		return (-num);
	else
		return (num);
}

void	draw_line_dda(t_tools *tools, float x2, float y2)
{
	int		i;
	float	steps;
	float	x;
	float	y;

	i = 0;
	if (fabs((x2 - tools->player_x)) > fabs((y2 - tools->player_y)))
		steps = (int)fabs((x2 - tools->player_x));
	else
		steps = (int)fabs((y2 - tools->player_y));
	x = tools->player_x;
	y = tools->player_y;
	while (i <= steps)
	{
		if ((int)y % 50 == 0 || (int)x % 50 == 0)
			my_mlx_pixel_put(&tools->img, x, y, YELLOW);
		x += (x2 - tools->player_x) / steps;
		y += (y2 - tools->player_y) / steps;
		i++;
	}
}
