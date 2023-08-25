/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 10:06:17 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/25 10:35:14 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	initiation(t_tools *tools)
{
	tools->pars->ptr = tools;
	tools->pars->C_B = -1;
	tools->pars->C_G = -1;
	tools->pars->C_B = -1;
	tools->pars->F_R = -1;
	tools->pars->F_G = -1;
	tools->pars->F_B = -1;
	tools->pars->map = NULL;
	tools->pars->north_path = NULL;
	tools->pars->south_path = NULL;
	tools->pars->west_path = NULL;
	tools->pars->east_path = NULL;
	tools->pars->land_range = 0;
}

void	ft_draw(t_tools *tools, int start_y, int start_x, int red)
{
	int y = 0;
	int x = 0;
	while (y < 50)
	{
		x = 0;
		while(x < 50)
		{
			my_mlx_pixel_put(&tools->img, start_x + x, start_y + y, red);
			my_mlx_pixel_put(&tools->img, start_x + x, start_y, 0xffd700);
			x++;
		}
			my_mlx_pixel_put(&tools->img, start_x , start_y + y, 0xffd700);
			y++;
	}
}

void draw_direction_line(t_tools *tools,float angle)
{
    int line_length = 30;

    int x;
	int	y;
	int i = 0;
    while(i <= line_length) 
	{
        x = tools->player_x + i * cos(angle);
        y = tools->player_y + i * sin(angle);
        my_mlx_pixel_put(&tools->img, x, y, 0x00FF00); // Green color
		i++;
    }
}
void	orientations(t_tools *tools)
{
	float angle = tools->angle * (3.14159265 / 180.0);
	tools->angle_rad = angle;
	tools->x_direction = tools->x_direction * cos(angle);
	tools->y_direction = tools->y_direction * sin(angle);
	draw_direction_line(tools,angle);
}
void	put_player(t_tools *tools)
{
	int x = tools->player_x - 5;
	int y = tools->player_y - 5;
	int i = 0;
	int j = 0;
	
	while (i < 10)
	{
		while (j < 10)
		{
			my_mlx_pixel_put(&tools->img, x + i, y + j, 0xFFFFFF);
			j++;
		}
		j = 0;
		i++;
	}
	orientations(tools);
}
int	move_cos(t_tools *tools)
{
	int tmp;
	tmp = tools->player_x + cos(tools->angle_rad) * 10 ;
	return(tmp);
}
int	move_sin(t_tools *tools)
{
	int tmp;
	tmp = tools->player_y + sin(tools->angle_rad) * 10 ;
	return(tmp);
}

int key_codes(int keycode, t_tools *tools)
{
	int x;
	int y;
	x = (tools->player_x);
	y = (tools->player_y);
	if (keycode == CAMERA_LEFT)
		tools->angle -= 10;
	if (keycode == CAMERA_RIGHT)
		tools->angle += 10;
	if (keycode == LEFT && tools->pars->land[y / 50][(x - 10) / 50] != '1')
		tools->player_x -= 10;
	else if (keycode == RIGHT && tools->pars->land[y / 50][(x + 10) / 50] != '1')
	{
		tools->player_x = tools->player_x + cos(tools->angle_rad) * 10 ;
		tools->player_y = tools->player_y + sin(tools->angle_rad) * 10 ;
	}
	else if (keycode == DOWN && tools->pars->land[(y + 10) / 50][x / 50] != '1')
	{
		tools->player_x = tools->player_x + cos(tools->angle_rad) * 10 ;
		tools->player_y = tools->player_y + sin(tools->angle_rad) * 10 ;
	}
	else if (keycode == UP && tools->pars->land[(move_sin(tools)) / 50][move_cos(tools) / 50] != '1')
	{
		tools->player_x += cos(tools->angle_rad) * 10 ;
		tools->player_y = tools->player_y + sin(tools->angle_rad) * 10 ;
	}
	else if (keycode == ESC)
		exit(0);
	put_map(tools);
	mlx_put_image_to_window(tools->mlx, tools->win, tools->img.img, 0, 0);
	return (0);
}

void	put_map(t_tools *tools)
{
	int i = 0;
	int j = 0;
	mlx_clear_window(tools->mlx, tools->win);
	while (tools->pars->land[i])
	{
		j = 0;
		while (tools->pars->land[i][j])
		{
			if(tools->pars->land[i][j] == '1')
				ft_draw(tools, i * 50, j * 50, RED);
			else if(tools->pars->land[i][j] == '0' || tools->pars->land[i][j] == 'N' || tools->pars->land[i][j] == 'S' \
						|| tools->pars->land[i][j] == 'W' || tools->pars->land[i][j] == 'E')
				ft_draw(tools, i * 50, j * 50, BLUE);
			j++;
		}
		// my_mlx_pixel_put(&tools->img, i, j, 0xffd700);
		i++;
	}
	put_player(tools);
	mlx_put_image_to_window(tools->mlx, tools->win, tools->img.img, 0, 0);
	return;
}

int	biggest_line(t_tools *tools)
{
	int lenght;
	int	i;
	int	j;

	lenght = 0;
	i = 0;
	while (tools->pars->land[i])
	{
		j = 0;
		while (tools->pars->land[i][j])
		{
			j++;
		}
		if(lenght <= j)
			lenght = j;
		i++;
	}
	return(lenght);
}
void	graphic(t_tools *tools)
{
	tools->mlx = mlx_init();
	tools->win = mlx_new_window(tools->mlx, (biggest_line(tools) * 50), (50 * (tools->pars->land_range + 1)), "cub3D");
	tools->img.img = mlx_new_image(tools->mlx, (biggest_line(tools) * 50), (50 * (tools->pars->land_range + 1)));
	tools->img.addr = mlx_get_data_addr(tools->img.img, &tools->img.bits_per_pixel, &tools->img.line_length, &tools->img.endian);
	tools->player_x = (tools->player_x * 50)+25;
	tools->player_y = (tools->player_y * 50)+25;
	// printf("player x = %d\n",tools->player_x);
	// printf("player orientation = %d\n",tools->orientation);
	put_map(tools);
	// draw_direction(tools);
	mlx_put_image_to_window(tools->mlx, tools->win, tools->img.img, 0, 0);
	mlx_hook(tools->win, 2, 1, key_codes, tools);
	mlx_loop(tools->mlx);
} 
int main(int argc, char **argv)
{
	t_tools tools;
	
	valid_entry(argc, argv, &tools);
	graphic(&tools);
}