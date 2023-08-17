/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:42:04 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/17 14:31:57 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	if_line_of_walls(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if(line[i] != '1' && line[i] != ' ')
		{
			error_map();
		}
		i++;
	}
	
}
void	left_wall(t_pars *pars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pars->land[i])
	{
		if(pars->land[i][j] == ' ')
		{
			j++;
			continue;
		}
		else if(pars->land[i][j] == '1')
		{
			j = 0;
			i++;
		}
		else
			error_map();
	}
}

int	allowed_contact(char c)
{
	if(c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return(1);
	return(0);
}

void	zero_sides_verification(char **land, int pos_i, int pos_j)
{
	if(allowed_contact(land[pos_i - 1][pos_j]))
		error_map();
	else if(allowed_contact(land[pos_i + 1][pos_j]))
		error_map();
	else if(allowed_contact(land[pos_i][pos_j + 1]))
		error_map();
	else if(allowed_contact(land[pos_i][pos_j - 1]))
		error_map();
}
void	if_valid_inside_lines(t_pars *pars)
{
	int		i;
	int		j;

	i = 1;
	while (pars->land[i] && i < pars->land_range)
	{
		j = 0;
		while(pars->land[i][j] == ' ' || pars->land[i][j] == '\t')
			j++;
		while (pars->land[i][j] != '\n' && pars->land[i][j] != '\0')
		{
			if(pars->land[i][j] == '0')
			{
				zero_sides_verification(pars->land, i,j);
				j++;
				continue;
			}
			j++;
		}
		i++;
	}
}
