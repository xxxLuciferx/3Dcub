/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 10:06:17 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/24 10:47:46 by khaimer          ###   ########.fr       */
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

void	put_player(t_tools *tools)
{
	int i = 0;
	int j = 0;
	int line = 50;
	while (i < 10)
	{
		while (j < 10)
		{
			my_mlx_pixel_put(&tools->img, tools->player_x + i - 5, tools->player_y + j - 5, 0xffd700);
			j++;
		}
		j = 0;
		i++;
	}
	if(tools->orientation == 2)
	{
		while (line--)
			my_mlx_pixel_put(&tools->img, tools->player_x + line, tools->player_y, 0x00FF00);
	}
}

void	rendering_after_move(t_tools *tools, int start_y, int start_x)
{
	
	int i = (start_x - 20) /50;
	int j = (start_y - 20) /50;
	
	int	end_x = ((start_x - 20) / 50 ) +1;
	int	end_y =((start_y - 20) / 50 ) +1;
	while (i <= end_x)
	{
		j = ((start_y - 20) / 50 ) - 1;
		while (j <= end_y )
		{
			if(tools->pars->land[i][j] == '1')
				ft_draw(tools, i * 50, j * 50, RED);
			else
				ft_draw(tools, i * 50, j * 50, BLUE);
			j++;
		}
		my_mlx_pixel_put(&tools->img, i, j, 0xffd700);
		i++;
	}
	put_player(tools);
}

int key_codes(int keycode, t_tools *tools)
{
	int x;
	int y;
	x = (tools->player_x);
	y = (tools->player_y);
	if (keycode == LEFT && tools->pars->land[y / 50][(x -10)/ 50] != '1')
		tools->player_x -= 10;
	else if (keycode == RIGHT && tools->pars->land[y / 50][(x +10)/ 50] != '1')
		tools->player_x += 10;
	else if (keycode == DOWN && tools->pars->land[(y +10)/ 50][x / 50] != '1')
		tools->player_y += 10;
	else if (keycode == UP && tools->pars->land[(y -10)/ 50][x / 50] != '1')
		tools->player_y -= 10;
	else if (keycode == ESC)
		exit(0);
		put_map(tools);
	// rendering_after_move(tools,tools->player_x,tools->player_y);
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
	tools->player_x = (tools->player_x * 50)+20;
	tools->player_y = (tools->player_y * 50)+20;
	// printf("player x = %d\n",tools->player_x);
	printf("player orientation = %d\n",tools->orientation);
	put_map(tools);
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