/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 10:06:17 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/19 12:35:27 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	int x =0;
	while (y <= 50)
	{
		x = 0;
		while(x <= 50)
		{
			mlx_pixel_put(tools->mlx, tools->win, start_x + x, start_y+ y, red);
			x++;
		}
		y++;
	}
}
void	move_player(t_tools *tools, int y, int x)
{
	printf("%c\n",tools->pars->land[y][x]);
	printf("%d, %d\n",tools->player_y,tools->player_x);
	
	
	char c;
	if(tools->pars->land[y][x] != '1')
	{
		c = tools->pars->land[y][x];
		tools->pars->land[y][x] = tools->pars->land[tools->player_y][tools->player_x];
		tools->pars->land[tools->player_y][tools->player_x] = c;
	}
	tools->player_x = x;
	tools->player_y = y;
}


int key_codes(int keycode, t_tools *tools)
{
	printf("jjjjjj\n");
	if (keycode == LEFT)
		move_player(tools, tools->player_y, tools->player_x - 1);	
	else if (keycode == RIGHT)
		move_player(tools, tools->player_y, tools->player_x + 1);	
	else if (keycode == DOWN)
		move_player(tools, tools->player_y + 1, tools->player_x);	
	else if (keycode == UP)
		move_player(tools, tools->player_y - 1,  tools->player_x);	
	else if (keycode == ESC)
		exit(0);
	mlx_clear_window(tools->mlx, tools->win);
	put_map(tools);
	
	return (0);
}

void	put_map(t_tools *tools)
{
	int i = 0;
	int j = 0;
	int red = 0xFF0000;
	while (tools->pars->land[i])
	{
		j = 0;
		while (tools->pars->land[i][j])
		{
			if(tools->pars->land[i][j] == '1')
				ft_draw(tools, i * 50, j * 50, red);
			else if(tools->pars->land[i][j] == 'N')
				ft_draw(tools, i * 50, j * 50, 0xFF);
			j++;
		}
		i++;
	}
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
	put_map(tools);
	mlx_key_hook(tools->win, key_codes, tools);
	mlx_loop(tools->mlx);
}
int main(int argc, char **argv)
{
	t_tools tools;
	
	valid_entry(argc, argv, &tools);
	graphic(&tools);
}