/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 10:06:17 by khaimer           #+#    #+#             */
/*   Updated: 2023/09/14 19:57:38 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	intiate_textures(t_tools *tools)
{
	t_data	*tex;

	tex = tools->tex;
	tex[0].img = mlx_xpm_file_to_image(tools->mlx, tools->pars->east_path,
			&tools->width, &tools->height);
	tex[1].img = mlx_xpm_file_to_image(tools->mlx, tools->pars->south_path,
			&tools->width, &tools->height);
	tex[2].img = mlx_xpm_file_to_image(tools->mlx, tools->pars->north_path,
			&tools->width, &tools->height);
	tex[3].img = mlx_xpm_file_to_image(tools->mlx, tools->pars->west_path,
			&tools->width, &tools->height);
	if (!tex[0].img || !tex[1].img || !tex[2].img || !tex[3].img)
		file_not_found(tools);
	tex[0].addr = mlx_get_data_addr(tex[0].img, &tex[0].bits_per_pixel,
			&tex[0].line_length, &tex[0].endian);
	tex[1].addr = mlx_get_data_addr(tex[1].img, &tex[1].bits_per_pixel,
			&tex[1].line_length, &tex[1].endian);
	tex[2].addr = mlx_get_data_addr(tex[2].img, &tex[2].bits_per_pixel,
			&tex[2].line_length, &tex[2].endian);
	tex[3].addr = mlx_get_data_addr(tex[3].img, &tex[3].bits_per_pixel,
			&tex[3].line_length, &tex[3].endian);
	if (!tex[0].addr || !tex[1].addr || !tex[2].addr || !tex[3].addr)
		file_not_found(tools);
}

void	initiation(t_tools *tools)
{
	tools->pars->ptr = tools;
	tools->pars->c_r = -1;
	tools->pars->c_g = -1;
	tools->pars->c_b = -1;
	tools->pars->f_r = -1;
	tools->pars->f_g = -1;
	tools->pars->f_b = -1;
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
	int	lenght;
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
		if (lenght <= j)
			lenght = j;
		i++;
	}
	return (lenght);
}

void	graphic(t_tools *tools)
{
	int	p_line;
	int	p_width;

	p_line = biggest_line(tools) * 50;
	p_width = tools->pars->land_range * 50;
	tools->lenght = p_line;
	tools->size = p_width;
	if (p_line > MAC_PX || p_width > MAC_PY)
	{
		printf("Error\nResolution is too big\n");
		exit(1);
	}
	tools->mlx = mlx_init();
	tools->win = mlx_new_window(tools->mlx, p_line, p_width, "cub3D");
	tools->img.img = mlx_new_image(tools->mlx, p_line, p_width);
	tools->img.addr = mlx_get_data_addr(tools->img.img, \
	&tools->img.bits_per_pixel, &tools->img.line_length, &tools->img.endian);
	intiate_textures(tools);
	tools->player_x = (tools->player_x * 50) + 25;
	tools->player_y = (tools->player_y * 50) + 25;
	draw_fov(tools);
	mlx_put_image_to_window(tools->mlx, tools->win, tools->img.img, 0, 0);
	mlx_hook(tools->win, 2, 1, key_codes, tools);
	mlx_hook(tools->win, 17, 0, close_window, tools);
	mlx_loop(tools->mlx);
}

int	main(int argc, char **argv)
{
	t_tools	tools;

	valid_entry(argc, argv, &tools);
	graphic(&tools);
}
