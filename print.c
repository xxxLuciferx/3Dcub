/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:09:53 by yichiba           #+#    #+#             */
/*   Updated: 2023/09/06 15:27:09 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_rays(t_tools *tools)
{
	t_ray **rays = tools->rays;
	int i = 0;
	while (i < tools->lenght)
	{
		printf("%d\n", i);
		printf("***********************************\n");
		printf("ray_direction[%d] = %c\n", rays[i]->indice, rays[i]->dir);
		printf("ray_x[%d] = %f\n", rays[i]->indice, rays[i]->x);
		printf("ray_y[%d] = %f\n", rays[i]->indice, rays[i]->y);
		printf("ray_angle[%d] = %f\n", rays[i]->indice, rays[i]->angle);
		printf("ray_len[%d] = %f\n", rays[i]->indice, rays[i]->len);
		i++;
	}
}