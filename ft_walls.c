/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:42:04 by khaimer           #+#    #+#             */
/*   Updated: 2023/09/11 18:47:05 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	if_line_of_walls(t_pars *pars, char *land)
{
	int	i;

	i = 0;
	while (land && land[i] != '\n' && land[i] != '\0')
	{
		if (land[i] != '1' && land[i] != ' ')
			error_map(pars->ptr);
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
		if (pars->land[i][j] == ' ')
		{
			j++;
			continue ;
		}
		else if (pars->land[i][j] == '1')
		{
			j = 0;
			i++;
		}
		else
		{
			free_map(pars->land);
			error_map(pars->ptr);
		}
	}
}

int	allowed_contact(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W' && c != 'E')
	{
		// printf("c = %c\n", c);
		return (1);
	}
	return (0);
}

void	zero_sides_verification(t_pars *pars, int pos_i, int pos_j)
{
	if (allowed_contact(pars->land[pos_i - 1][pos_j]))
	{
		free_map(pars->land);
		error_map(pars->ptr);
	}
	else if (allowed_contact(pars->land[pos_i + 1][pos_j]))
	{
		free_map(pars->land);
		error_map(pars->ptr);
	}
	else if (allowed_contact(pars->land[pos_i][pos_j + 1]))
	{
		free_map(pars->land);
		error_map(pars->ptr);
	}
	else if (allowed_contact(pars->land[pos_i][pos_j - 1]))
	{
		free_map(pars->land);
		error_map(pars->ptr);
	}
}
void	if_valid_inside_lines(t_pars *pars)
{
	int	i;
	int	j;

	i = 1;
	while (pars->land[i] && i < pars->land_range)
	{
		j = 0;
		while (pars->land[i][j] == ' ' || pars->land[i][j] == '\t')
			j++;
		while (pars->land[i][j] != '\n' && pars->land[i][j] != '\0')
		{
			if (pars->land[i][j] == '0')
			{
				zero_sides_verification(pars, i, j);
				j++;
				continue ;
			}
			j++;
		}
		i++;
	}
}
