/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 11:20:44 by yichiba           #+#    #+#             */
/*   Updated: 2023/09/07 14:21:34 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		check_intersections_horizental(float x, float y , float angle,t_tools *tools )
{
	float 	width;
	float 	height;

	width	= tools->lenght;
	height	= tools->size;
	char **map = tools->pars->land;
    if( x > width  || x < 50|| y > height || y < 50)
    	return(-1);
	if((angle >=0 && angle < M_PI_2) && y+1 <=height  && x+1 <= width &&  (map[(int)((y+1)/50)][(int)(x/ 50)] == '1' ))
		return(1);
	else if((angle >= M_PI_2 && angle < M_PI) && y+1 <= height  && x-1 >= 0 && (map[(int)((y+1)/50)][(int)(x/ 50)] == '1' ))
		return(1);
	else if((angle >= M_PI && angle < 3 * M_PI_2) && y-1 >=0  && x-1 >= 0 && (map[(int)((y-1)/50)][(int)(x/ 50)] == '1' ))
		return(1);
	else if((angle >= 3 * M_PI_2 && angle <= 2 * M_PI) && y-1 >=0 && y <= height-1 && x +1 <= width && (map[(int)((y-1)/50)][(int)(x/ 50)] == '1' ))
		return(1);
	return(0);
}
int		check_intersections_vertical(float x, float y , float angle,t_tools *tools )
{
	float 	width;
	float 	height;

	width	= tools->lenght;
	height	= tools->size;
	char **map = tools->pars->land;
    if( x > width  || x < 50 || y > height || y < 50)
        return(-1);
	if((angle >=0 && angle < M_PI_2) && y+1 <=height  && x+1 <= width &&  (map[(int)(y/50)][(int)((x+1)/ 50)] == '1' ))
		return(1);
	else if((angle >= M_PI_2 && angle < M_PI) && y+1 <= height  && x-1 >= 0 && (map[(int)(y/50)][(int)((x-1)/ 50)] == '1' ))
		return(1);
	else if((angle >= M_PI && angle < 3 * M_PI_2) && y-1 >=0  && x-1 >= 0 && (map[(int)(y/50)][(int)((x-1)/ 50)] == '1' ))
		return(1);
	else if((angle >= 3 * M_PI_2 && angle <= 2 * M_PI) && y-1 >=0 && y <= height-1 && x +1 <= width && (map[(int)(y/50)][(int)((x+1)/ 50)] == '1' ))
		return(1);
	return(0);
}

int     intersection_horiz(t_tools *tools,t_hit *h,float angle ,int i)
{
		if (angle < M_PI && angle > 0)
			h->y = ((int)(tools->player_y /50 + 1)+ i) * 50;
		else
			h->y = ((int)(tools->player_y /50) - i) * 50;
		if (angle > (M_PI / 2) || angle < (3 * M_PI) / 2)
			h->x =  tools->player_x - ((tools->player_y - h->y) / tan(angle));
		else
			h->x = tools->player_x + ((tools->player_y - h->y) / tan(angle));
        int check = check_intersections_horizental(h->x,h->y,angle, tools);
		if( check == -1)
			return(-1);	
		if(check == 1)
			return(1);
		return(intersection_horiz(tools, h,angle,i+1));
}

int		intersection_verti(t_tools *tools, t_hit *v,float angle,int i)
{
	if (angle < (M_PI / 2) || angle > (3 * M_PI) / 2)
		v->x = ((int)(tools->player_x / 50 + 1 )+ i) * 50 ;
	else
		v->x = ((int)(tools->player_x / 50 )- i)* 50;
	if (angle < M_PI && angle > 0)
		v->y = tools->player_y - ((tools->player_x - v->x) * tan(angle));
	else
		v->y = tools->player_y + ((v->x - tools->player_x) * tan(angle));
	int check = check_intersections_vertical(v->x,v->y,angle, tools);
	if( check == -1)
		return(-1);	
	if(check == 1)
		return(1);
	return(intersection_verti(tools, v,angle,i+1));
}

void draw_line_dda(t_tools *tools, float x2, float y2)
{
	int i = 0;
	float steps;
    float x;
    float y;
    float x_increment;
    float y_increment;

	if (fabs((x2 - tools->player_x)) > fabs((y2 - tools->player_y))) 
		steps = (int)fabs((x2 - tools->player_x));
	else 
    	steps = (int)fabs((y2 - tools->player_y));
	x_increment = (x2 - tools->player_x) / steps;
	y_increment = (y2 - tools->player_y) / steps;
	x = tools->player_x;
	y = tools->player_y;
	while(i <= 50)
	{
        my_mlx_pixel_put(&tools->img, x -(2 *x_increment), y-(2 * y_increment), 0x00FF00);
        my_mlx_pixel_put(&tools->img, x -x_increment, y-y_increment, 0x00FF00);
        my_mlx_pixel_put(&tools->img, x, y, 0x00FF00);
        my_mlx_pixel_put(&tools->img, x+x_increment, y+y_increment, 0x00FF00);
        my_mlx_pixel_put(&tools->img, x +(2 *x_increment), y+(2 * y_increment), 0x00FF00);
        x += x_increment;
        y += y_increment;
		i++;
    }
}

float  absolutevalue(double num)
{
    if (num == INT_MIN) 
        return -(num + 3);
    else if (num < 0)
        return -num;
    else
        return num;
}
float	 ray_lenght(t_tools *tools,float x2, float y2) 
{
	float distance = 0;
	float dist = 0;
	double dx = x2 - tools->player_x;
	double dy = y2 - tools->player_y;
	distance  = sqrt(dx * dx + dy * dy);
	dist = absolutevalue(distance);
	return (dist);
}

float	intersection(t_tools *tools,t_ray *ray, float angle)
{
	t_hit	horizental;
	t_hit	vertical;
	float	distance_h;
	float	distance_v;
	
	intersection_verti(tools, &vertical, angle, 0);
	intersection_horiz(tools, &horizental, angle, 0);
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
