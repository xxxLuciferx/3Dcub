/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:18:57 by yichiba           #+#    #+#             */
/*   Updated: 2023/09/14 14:44:22 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	normalize_angle(float angle)
{
	angle = fmodf(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

t_ray	**creat_rays_table(int len)
{
	t_ray	**rays;
	int		i;

	i = 0;
	rays = (t_ray **)malloc(len * sizeof(t_ray *));
	if (rays == NULL)
		return (NULL);
	while (i < len)
	{
		rays[i] = ft_lstnew(i);
		i++;
	}
	return (rays);
}

void	draw_directions(t_tools *tools)
{
	int	i;

	i = 0;
	put_map(tools);
	while (i < tools->lenght)
	{
		draw_line_dda(tools, tools->rays[i]->x, tools->rays[i]->y);
		i++;
	}
}

void	orientations(t_tools *tools)
{
	float	angle;

	angle = tools->angle * (M_PI / RAD);
	tools->angle_rad = angle;
}
