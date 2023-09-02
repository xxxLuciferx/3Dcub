/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:46:35 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/31 11:08:53 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	if_valid_string(char *line)
{
	int	i;
	int	counter;

	i = 1;
	counter = 0;
	while (line[i])
	{
		if(line[i] != ' ' && (line[i] > '9' || line[i] < '0'))
		{
			if(line[i] == ',')
				counter++;
			else
				error_colors();
		}
		i++;
	}
	if(counter != 2)
		error_colors();
}

unsigned int		ceiling_colors(t_pars *pars, int i)
{
	char	**tmp;
	
	if_valid_string(pars->map[i]);
	tmp = ft_split(pars->map[i], ",");
	pars->C_R = ft_atoi(tmp[0]);
	pars->C_G = ft_atoi(tmp[1]);
	pars->C_B = ft_atoi(tmp[2]);
	free_arrays(tmp);
	if(pars->C_R < 0 || pars->C_R > 255)
		error_colors();
	if(pars->C_G < 0 || pars->C_G > 255)
		error_colors();
	if(pars->C_B < 0 || pars->C_B > 255)
		error_colors();
	return ((pars->C_R << 16) | (pars->C_G << 8) | pars->C_B);
	
}

unsigned int	floor_colors(t_pars *pars, int i)
{
	char	**tmp;
	
	if_valid_string(pars->map[i]);
	tmp = ft_split(pars->map[i], ",");
	pars->F_R = ft_atoi(tmp[0]);
	pars->F_G = ft_atoi(tmp[1]);
	pars->F_B = ft_atoi(tmp[2]);
	free_arrays(tmp);
	if(pars->F_R < 0 || pars->F_R > 255)
		error_colors();
	if(pars->F_G < 0 || pars->F_G > 255)
		error_colors();
	if(pars->F_B < 0 || pars->F_B > 255)
		error_colors();
	return ((pars->F_R << 16) | (pars->F_G << 8) | pars->F_B);
}