/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:46:35 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/15 11:48:23 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		ceiling_colors(t_pars *pars, int i)
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
}

void	floor_colors(t_pars *pars, int i)
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
}