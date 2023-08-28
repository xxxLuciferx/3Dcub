/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:09:53 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/28 22:23:14 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    print_rays(t_ray *rays)
{
	int i = 0;
    while (rays)
	{
		printf("%d\n",i++);
        // printf("***********************************\n");
		//     printf("ray_x[%d] = %f\n",rays->indice, rays->x);
		//     printf("ray_x[%d] = %f\n",rays->indice, rays->y);
		//     printf("ray_angle[%d] = %f\n",rays->indice, rays->angle);
		//     printf("ray_len[%d] = %d\n",rays->indice, rays->len);
		rays = rays->next;
	}
}