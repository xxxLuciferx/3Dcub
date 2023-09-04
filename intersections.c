/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 11:20:44 by yichiba           #+#    #+#             */
/*   Updated: 2023/09/04 15:00:43 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		check_intersections(float x, float y , float angle,t_tools *tools )
{
	
	char **map = tools->pars->land;
    if( x > tools->lenght  || x < 0 || y > tools->size || y < 0)
                return(-1);
	if(y+1 <=tools->size  && x+1 <= tools->lenght && (angle >=0 && angle < M_PI_2) && (map[(int)(y+1)/50][(int)(x+1)/ 50] == '1' || map[(int)(y+1)/50][(int)(x+1)/ 50] == ' '))
			return(1);
	else if(y+1 <= tools->size  && x-1 >= 0 && (angle >= M_PI_2 && angle < M_PI) && (map[(int)(y+1)/50][(int)(x-1)/ 50] == '1' || map[(int)(y+1)/50][(int)(x-1)/ 50] == ' '))
			return(1);
	else if(y-1 >=0  && x-1 >= 0 && (angle >= M_PI && angle < 3 * M_PI_2) && (map[(int)(y-1)/50][(int)(x-1)/ 50] == '1' || map[(int)(y-1)/50][(int)(x-1)/ 50] == ' '))
			return(1);
	else if(y-1 >=0  && x +1 <= tools->lenght && (angle >= 3 * M_PI_2 && angle <= 2 * M_PI) && (map[(int)(y-1)/50][(int)(x+1)/ 50] == '1' || map[(int)(y-1)/50][(int)(x+1)/ 50] == ' '))
			return(1);
	return(0);
}

int     intersection_horiz(t_tools *tools, float *x, float *y,float angle )
{
	int i  = 0;
	while(1)
	{
		
		if (angle < M_PI && angle > 0)
			*y = ((int)tools->player_y /50 + i+ 1) * 50;
		else
			*y = ((int)tools->player_y /50 - i) * 50;
			
		if (angle > (M_PI / 2) || angle < (3 * M_PI) / 2)
			*x = (int) tools->player_x - (((int)tools->player_y - *y) / tan(angle));
		else
			*x = (int)tools->player_x + (((int)tools->player_y - *y) / tan(angle));
        int check = check_intersections(*x,*y,angle, tools);
		if( check == -1)
			return(-1);	
		if(check == 1)
			return(1);	
	i++;
	}
}

int		intersection_verti(t_tools *tools, float *x, float *y,float angle)
{
	int i = 0;
	while(1)
	{
		if (angle < (M_PI / 2) || angle > (3 * M_PI) / 2)
			*x = ((int)tools->player_x / 50 + 1 + i) * 50 ;
		else
			*x = ((int)tools->player_x / 50 - i)* 50;
		if (angle < M_PI && angle > 0)
			*y = (int)tools->player_y - (((int)tools->player_x - *x) * tan(angle));
		else
			*y = (int)tools->player_y + ((*x -(int) tools->player_x) * tan(angle));
		int check = check_intersections(*x,*y,angle, tools);
		if( check == -1)
			return(-1);	
		if(check == 1)
			return(1);	
		i++;
	}
}

void draw_line_dda(t_tools *tools, float x2, float y2)
{
    float x1 = tools->player_x;
    float y1 = tools->player_y;
    float dx = x2 - x1;
    float dy = y2 - y1;

    int steps = (int)(fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy));

    float x_increment = dx / steps;
    float y_increment = dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++)
	{
        my_mlx_pixel_put(&tools->img, x-1, y-1, 0x00FF00);
        x += x_increment;
        y += y_increment;
    }
}

unsigned int  absolutevalue(double num)
{
    if (num == INT_MIN) 
        return -(num + 3);
    else if (num < 0)
        return -num;
    else
        return num;
}
unsigned int ray_lenght(t_tools *tools,float x2, float y2) 
{
	int distance = 0;
	unsigned int dist = 0;
	double dx = x2 - tools->player_x;
	double dy = y2 - tools->player_y;
	distance  = sqrt(dx * dx + dy * dy);
	dist = absolutevalue(distance);
	return (dist);
}
	
int	intersection(t_tools *tools,t_ray *ray, float angle)
{
	t_hit	horizental;
	t_hit	vertical;
	unsigned int	distance_h;
	unsigned int	distance_v;
	
	intersection_verti(tools, &vertical.x, &vertical.y,angle);
	intersection_horiz(tools, &horizental.x, &horizental.y,angle);
	distance_h = ray_lenght(tools,horizental.x,horizental.y);
	distance_v = ray_lenght(tools,vertical.x,vertical.y);
	if(distance_h > distance_v )
		{
			ray->x = vertical.x;
			ray->y = vertical.y;
			ray->dir = 'v';
			return(distance_v);
		}
	else
		{
			ray->x = horizental.x;
			ray->y = horizental.y;
			ray->dir = 'h';
			return(distance_h);
		}
}
