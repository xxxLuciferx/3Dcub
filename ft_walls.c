/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:42:04 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/15 13:27:22 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	if_line_of_walls(char *line, t_pars *pars, int line_pos)
{
	int i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if(line[i] != '1')
		{
			free(pars->land[0]);
			line_pos = 0;
			if(line[i] == ' ')
				check_next_wall(pars, i, line_pos);
			else
				error_map();
		}
		i++;
	}
}

void	if_sides_are_walls(t_pars *pars)
{
	// int i;

	// i = 0;
	//-----------------------------------------------------------------------
	// if_line_of_walls(pars->land[0], pars, 0);
	if_line_of_walls(pars->land[0], pars, pars->land_range);
	// if_line_of_walls(pars->land[pars->land_range], pars, pars->land_range);
	// if_line_of_walls(pars->land[pars->land_range], pars, pars->land_range);
	//-----------------------------------------------------------------------
	// if_walls(pars->land[pars->land_range]);
	// printf("%s\n", pars->land[pars->land_range - 1]);
	// if_walls(pars->land[pars->land_range]);
	// printf("%s\n", pars->land[0]);
	// printf("%d\n", pars->land_range);
	// if_walls(map[i - 1]);
	// while (--i)
	// {
	// 	if(map[i][0] != '1')
	// 		error_map();
	// 	if(map[i][ft_strlen(map[i]) - 1] != '1')
	// 		error_map();
	// }
}

void	ft_surrounded_walls(t_pars *pars)
{
	if_sides_are_walls(pars);
}