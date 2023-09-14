/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:46:35 by khaimer           #+#    #+#             */
/*   Updated: 2023/09/14 23:49:17 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	if_valid_string(t_pars *pars, char *line)
{
	int	i;
	int	counter;

	i = 1;
	counter = 0;
	while (line[i])
	{
		if (line[i] != ' ' && (line[i] > '9' || line[i] < '0'))
		{
			if (line[i] == ',')
				counter++;
			else
				error_colors(pars);
		}
		i++;
	}
	if (counter != 2)
		error_colors(pars);
}

unsigned int	ceiling_colors(t_pars *pars, int i)
{
	char	**tmp;

	if_valid_string(pars, pars->map[i]);
	tmp = ft_split(pars->map[i], ",");
	if(tmp[0] == NULL || tmp[1] == NULL || tmp[2] == NULL)
		error_colors(pars);
	pars->c_r = ft_atoi(tmp[0]);
	pars->c_g = ft_atoi(tmp[1]);
	pars->c_b = ft_atoi(tmp[2]);
	free_arrays(tmp);
	if (pars->c_r < 0 || pars->c_r > 255)
		error_colors(pars);
	if (pars->c_g < 0 || pars->c_g > 255)
		error_colors(pars);
	if (pars->c_b < 0 || pars->c_b > 255)
		error_colors(pars);
	return ((pars->c_r << 16) | (pars->c_g << 8) | pars->c_b);
}

unsigned int	floor_colors(t_pars *pars, int i)
{
	char	**tmp;

	if_valid_string(pars, pars->map[i]);
	tmp = ft_split(pars->map[i], ",");
	if(tmp[0] == NULL || tmp[1] == NULL || tmp[2] == NULL)
		error_colors(pars);
	pars->f_r = ft_atoi(tmp[0]);
	pars->f_g = ft_atoi(tmp[1]);
	pars->f_b = ft_atoi(tmp[2]);
	free_arrays(tmp);
	if (pars->f_r < 0 || pars->f_r > 255)
		error_colors(pars);
	if (pars->f_g < 0 || pars->f_g > 255)
		error_colors(pars);
	if (pars->f_b < 0 || pars->f_b > 255)
		error_colors(pars);
	return ((pars->f_r << 16) | (pars->f_g << 8) | pars->f_b);
}
