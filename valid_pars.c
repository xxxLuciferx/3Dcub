/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:22:24 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/24 10:10:58 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	collect_direction(char c, t_pars *pars)
{
	if(c == 'N')
		pars->ptr->orientation = 2;
	else if(c == 'S')
		pars->ptr->orientation = 3;
	else if(c == 'E')
		pars->ptr->orientation = 1;
	else if(c == 'W')
		pars->ptr->orientation = 4;		
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
				collect_direction(pars->land[i][j], pars);
				counter++;
			}
			// else if(i != pars->land_range && pars->land[i][j] != '0' && pars->land[i][j] != '1' && i != 0)
			// 	error_map();
			j++;
		}
		i++;
	}
	// printf("%s\n", pars->land[pars->land_range]);
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
		ceiling_colors(pars, i);
	else if (pars->map[i][0] == 'F')
		floor_colors(pars, i);
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
	int	tmp;
	int i;
	
	i = 0;
	while (pars->map[pars->land_range])
		pars->land_range++;
	tmp = pars->land_range - 1;
	pars->land_range = pars->land_range - pos;
	pars->land = malloc(sizeof(char **) * pars->land_range + 1);
	pars->land_range = 0;
	while (pars->map[pos])
	{
		pars->land[i] = ft_strdup(pars->map[pos]);
		pos++;
		i++;
	}
	pars->land[i] = NULL;
	pars->land_range = i - 1;	
	if_player_exist(pars);
	// if_correct_map(pars);
}