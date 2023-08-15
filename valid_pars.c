/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:22:24 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/15 12:42:21 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"



void	if_one_player(char **land)
{
	int	i;
	int	j;
	int counter;

	i = 0;
	j = 0;
	counter = 0;
	while (land[i] != 0)
	{
		j = 0;
		while (land[i][j] != '\n' && land[i][j] != '\0')
		{
			if(land[i][j] == 'N' || land[i][j] == 'S' || land[i][j] == 'E' || land[i][j] == 'W')
				counter++;
			j++;
		}
		i++;
	}
	if(counter != 1)
		error_player();
}
void	if_player_exist(t_pars *pars)
{
	int	i;
	int	j;

	i = 0;
	if_one_player(pars->land);
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
	// pars->land
	pars->land_range = 0;
	// pars->land[tmp] = ft_strdup(pars->map[pos]);
	// printf("%s\n", pars->land[tmp]);
	while (pars->map[pos])
	{
		pars->land[i] = ft_strdup(pars->map[pos]);
		// printf("%s\n", pars->land[i]);
		pos++;
		i++;
	}
	pars->land_range = i - 1;	
	if_player_exist(pars);
	// if_correct_map(pars);
}