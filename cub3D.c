/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 10:06:17 by khaimer           #+#    #+#             */
/*   Updated: 2023/09/09 22:04:41 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


int	ara_lcolorr_r(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void	intiate_textures(t_tools *tools)
{
	// tools->tex = malloc(4*sizeof(t_data));
	tools->tex[0].img = mlx_xpm_file_to_image(tools->mlx, "./textures/wall.xpm",&tools->width, &tools->height);
	tools->tex[0].addr = mlx_get_data_addr(tools->tex[0].img, &tools->tex[0].bits_per_pixel, &tools->tex[0].line_length, &tools->tex[0].endian);

	
	tools->tex[1].img = mlx_xpm_file_to_image(tools->mlx, "./textures/wall2.xpm",&tools->width, &tools->height);
	tools->tex[1].addr = mlx_get_data_addr(tools->tex[1].img, &tools->tex[1].bits_per_pixel, &tools->tex[1].line_length, &tools->tex[1].endian);
	
	tools->tex[2].img = mlx_xpm_file_to_image(tools->mlx, "./textures/wall3.xpm",&tools->width, &tools->height);
	tools->tex[2].addr = mlx_get_data_addr(tools->tex[2].img, &tools->tex[2].bits_per_pixel, &tools->tex[2].line_length, &tools->tex[2].endian);
	
	tools->tex[3].img = mlx_xpm_file_to_image(tools->mlx, "./textures/wall4.xpm",&tools->width, &tools->height);
	tools->tex[3].addr = mlx_get_data_addr(tools->tex[3].img, &tools->tex[3].bits_per_pixel, &tools->tex[3].line_length, &tools->tex[3].endian);
	
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
	tools->rays = NULL;
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
	int p_line;
	int p_width;
	
	p_line = biggest_line(tools) * 50;
	p_width = tools->pars->land_range * 50;
	tools->lenght = p_line;
	tools->size = p_width;
	if(p_line > MAC_PX || p_width > MAC_PY)
	{
		printf("Error\nResolution is too big\n");
		exit(0);
	}
	tools->mlx = mlx_init();
	tools->win = mlx_new_window(tools->mlx, p_line, p_width, "cub3D");
	tools->img.img = mlx_new_image(tools->mlx, p_line, p_width);
	tools->img.addr = mlx_get_data_addr(tools->img.img, &tools->img.bits_per_pixel, &tools->img.line_length, &tools->img.endian);
	intiate_textures(tools);
	tools->player_x = (tools->player_x * 50) + 25;
	tools->player_y = (tools->player_y * 50) + 25;
	draw_fov(tools);
	
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