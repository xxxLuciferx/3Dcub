/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:29:16 by yichiba           #+#    #+#             */
/*   Updated: 2023/08/27 13:10:05 by yichiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int get_pixel_color_from_image(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}
int main()
{
    t_data img;
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 500, 500, "Pixel Color Example");
    img.img = mlx_new_image(mlx, 500, 500);

    int x = 100; 
    int y = 50;

    my_mlx_pixel_put(&img, x, y, 0x0000FF); 
    mlx_put_image_to_window(mlx, win,img.img, 0, 0);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    int color = get_pixel_color_from_image(&img, x, y);
    
    unsigned char red = (color >> 16) & 0xFF;
    unsigned char green = (color >> 8) & 0xFF;
    unsigned char blue = color & 0xFF;

    printf("Red: %d, Green: %d, Blue: %d\n", red, green, blue);
    mlx_loop(mlx);

    return 0;
}
