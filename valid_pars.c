/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:22:24 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/31 11:09:13 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	collect_direction(char c, t_pars *pars)
{
	pars->ptr->angle = 0 ;
	pars->ptr->x_direction = pars->ptr->player_x * 50 + 50 ;
	pars->ptr->y_direction = pars->ptr->player_y * 50 ;
	if(c == 'S')
			pars->ptr->angle = 90 ;
	else if(c == 'W')
			pars->ptr->angle = 180 ;
	else if(c == 'N')
			pars->ptr->angle = 270 ;
}

void	if_one_player(t_pars *pars)
{
	int	i;
	int	j;
	int counter;

	i = 0;
	j = 0;
	counter = 0;
	while (pars->land[i])
	{
		j = 0;
		while ( pars->land[i][j] != '\0')
		{
			if(pars->land[i][j] == 'N' || pars->land[i][j] == 'S' || pars->land[i][j] == 'E' || pars->land[i][j] == 'W')
			{
				pars->ptr->player_y = i;
				pars->ptr->player_x = j;
				collect_direction(pars->land[i][j], pars);
				counter++;
			}
			j++;
		}
		i++;
	}
	if(counter != 1)
		error_player();
}
void		if_player_exist(t_pars *pars)
{
	int	i;
	int	j;

	i = 0;
	if_one_player(pars);
	while (pars->land[i])
	{
		j = 0;
		while (pars->land[i][j] != '\n' && pars->land[i][j] != '\0')
		{
			if(pars->land[i][j] == 'N' || pars->land[i][j] == 'S' || pars->land[i][j] == 'E' || pars->land[i][j] == 'W')
			{
				pars->ptr->player_x = j;
				pars->ptr->player_y = i;
				return;
			}
			j++;
		}
		i++;
	}	
}

void	collect_texture_and_colors(t_pars *pars, int i)
{
	if (pars->map[i][0] == 'C')
		pars->ceilling_color = ceiling_colors(pars, i);
	else if (pars->map[i][0] == 'F')
		pars->floor_color = floor_colors(pars, i);
	else if (pars->map[i][0] == 'N' && pars->map[i][1] == 'O')
		north_path(pars, i);
	else if (pars->map[i][0] == 'S' && pars->map[i][1] == 'O')
		south_path(pars, i);
	else if (pars->map[i][0] == 'W' && pars->map[i][1] == 'E')
		west_path(pars, i);
	else if (pars->map[i][0] == 'E' && pars->map[i][1] == 'A')
		east_path(pars, i);
	
}

void	ft_map_copy(t_pars *pars, int pos)
{
	int i;
	
	i = 0;
	while (pars->map[pos +i])
		i++;
	pars->land_range = i;
	pars->land = malloc(sizeof(char *) * (pars->land_range + 1));
	i = 0;
	while (pars->map[pos])
	{
		pars->land[i] = ft_strdup(pars->map[pos]);
		pos++;
		i++;
	}
	pars->land[i] = NULL;
	if_player_exist(pars);
	// if_correct_map(pars);
}