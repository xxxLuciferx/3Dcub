/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 11:20:44 by yichiba           #+#    #+#             */
/*   Updated: 2023/09/14 20:01:18 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_intersections_horizental(float x, float y, float angle,
		t_tools *tools)
{
	float	width;
	float	height;
	char	**map;

	width = tools->lenght;
	height = tools->size;
	map = tools->pars->land;
	if (x > width || x < 50 || y > height || y < 50)
		return (-1);
	if ((angle >= 0 && angle < M_PI_2) && y + 1 <= height && x + 1 <= width
		&& (map[(int)((y + 1) / 50)][(int)(x / 50)] == '1'))
		return (1);
	else if ((angle >= M_PI_2 && angle < M_PI) && y + 1 <= height && x - 1 >= 0
		&& (map[(int)((y + 1) / 50)][(int)(x / 50)] == '1'))
		return (1);
	else if ((angle >= M_PI && angle < 3 * M_PI_2) && y - 1 >= 0 && x - 1 >= 0
		&& (map[(int)((y - 1) / 50)][(int)(x / 50)] == '1'))
		return (1);
	else if ((angle >= 3 * M_PI_2 && angle <= 2 * M_PI) && y - 1 >= 0 && \
		y <= height - 1 && x + 1 <= width && (map[(int)((y - 1) \
		/ 50)][(int)(x / 50)] == '1'))
		return (1);
	return (0);
}

int	check_intersections_vertical(float x, float y, float angle, t_tools *tools)
{
	float	width;
	float	height;
	char	**map;

	width = tools->lenght;
	height = tools->size;
	map = tools->pars->land;
	if (x > width || x < 50 || y > height || y < 50)
		return (-1);
	if ((angle >= 0 && angle < M_PI_2) && y + 1 <= height && x + 1 <= width
		&& (map[(int)(y / 50)][(int)((x + 1) / 50)] == '1'))
		return (1);
	else if ((angle >= M_PI_2 && angle < M_PI) && y + 1 <= height && x - 1 >= 0 \
	&& (map[(int)(y / 50)][(int)((x - 1) / 50)] == '1'))
		return (1);
	else if ((angle >= M_PI && angle < 3 * M_PI_2) && y - 1 >= 0 && x - 1 >= 0 \
	&& (map[(int)(y / 50)][(int)((x - 1) / 50)] == '1'))
		return (1);
	else if ((angle >= 3 * M_PI_2 && angle <= 2 * M_PI) && y - 1 >= 0 \
	&& y <= height - 1 && x + 1 <= width && (map[(int)(y / 50)][(int)((x \
	+ 1) / 50)] == '1'))
		return (1);
	return (0);
}

int	intersection_horiz(t_tools *tools, t_hit *h, float angle, int i)
{
	int	check;

	if (angle < M_PI && angle > 0)
		h->y = ((int)(tools->player_y / 50 + 1) + i) * 50;
	else
		h->y = ((int)(tools->player_y / 50) - i) * 50;
	if (angle > (M_PI / 2) || angle < (3 * M_PI) / 2)
		h->x = tools->player_x - ((tools->player_y - h->y) / tan(angle));
	else
		h->x = tools->player_x + ((tools->player_y - h->y) / tan(angle));
	check = check_intersections_horizental(h->x, h->y, angle, tools);
	if (check == -1)
		return (-1);
	if (check == 1)
		return (1);
	return (intersection_horiz(tools, h, angle, i + 1));
}

int	intersection_verti(t_tools *tools, t_hit *v, float angle, int i)
{
	int	check;

	if (angle < (M_PI / 2) || angle > (3 * M_PI) / 2)
		v->x = ((int)(tools->player_x / 50 + 1) + i) * 50;
	else
		v->x = ((int)(tools->player_x / 50) - i) * 50;
	if (angle < M_PI && angle > 0)
		v->y = tools->player_y - ((tools->player_x - v->x) * tan(angle));
	else
		v->y = tools->player_y + ((v->x - tools->player_x) * tan(angle));
	check = check_intersections_vertical(v->x, v->y, angle, tools);
	if (check == -1)
		return (-1);
	if (check == 1)
		return (1);
	return (intersection_verti(tools, v, angle, i + 1));
}

float	intersection(t_tools *tools, t_ray *ray, float angle)
{
	t_hit	horizental;
	t_hit	vertical;
	float	distance_h;
	float	distance_v;

	intersection_verti(tools, &vertical, angle, 0);
	intersection_horiz(tools, &horizental, angle, 0);
	distance_h = ray_lenght(tools, horizental.x, horizental.y);
	distance_v = ray_lenght(tools, vertical.x, vertical.y);
	if (distance_h > distance_v)
	{
		ray->x = vertical.x;
		ray->y = vertical.y;
		ray->dir = 'v';
		return (distance_v);
	}
	else
	{
		ray->x = horizental.x;
		ray->y = horizental.y;
		ray->dir = 'h';
		return (distance_h);
	}
}
