/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:42:04 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/16 11:00:53 by khaimer          ###   ########.fr       */
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
void	zero_sides_verification(char **land, int pos_i, int pos_j)
{
	if(land[pos_i - 1][pos_j] != '1' && land[pos_i - 1][pos_j] != '0' && land[pos_i - 1][pos_j] != 'N')
	{
		printf("%c", land[pos_i - 1][pos_j]);
		error_map();
	}
	else if(land[pos_i + 1][pos_j] != '1' && land[pos_i + 1][pos_j] != '0' && land[pos_i + 1][pos_j] != 'N')
	{

		printf("%c", land[pos_i + 1][pos_j]);
		error_map();
	}
	else if(land[pos_i][pos_j + 1] != '1' && land[pos_i][pos_j + 1] != '0' && land[pos_i][pos_j + 1] != 'N')
	{

		printf("%c", land[pos_i][pos_j + 1]);
		error_map();
	}
	else if(land[pos_i][pos_j - 1] != '1' && land[pos_i][pos_j - 1] != '0' && land[pos_i][pos_j - 1] != 'N')
	{
		printf("%c", land[pos_i][pos_j - 1]);
		error_map();	
	}
}
void	if_valid_inside_lines(t_pars *pars)
{
	int		i;
	int		j;
	char	c;

	i = 1;
	c = '0';
	printf("HOLA\n");
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
			else if (pars->land[i][j] == '1')
			{
				if(pars->land[i][j + 1] != '1' && pars->land[i][j + 1] != '0')
				{
					c = pars->land[i][j];
					// printf("%c\n", c);
				}
			}
			// if (pars->land[i][j] == '1' || pars->land[i][j] == '0')
			j++;
			// else
			// 	error_map();
		}
			// if(pars->land[i][j] == ' ' || pars->land[i][j] == '\n' || pars->land[i][j] == '\0')
			// 	c = pars->land[i][j - 1];
		// printf("%c\n",c);
		// if(c != '1')
		// 	error_map();
		i++;
	}
	printf("\nPERFECT\n");
	exit(0);
}
void	if_sides_are_walls(t_pars *pars)
{
	
	// int i;
	left_wall(pars);
	if_line_of_walls(pars->land[0]);
	if_line_of_walls(pars->land[pars->land_range]);
	if_valid_inside_lines(pars);
	
	// i = 0;
	//-----------------------------------------------------------------------
	// if_line_of_walls(pars->land[0], pars, pars->land_range);
	// if_line_of_walls(pars->land[pars->land_range], pars, pars->land_range);
	// if_line_of_walls(pars->land[pars->land_range], pars, pars->land_range);
	//-----------------------------------------------------------------------
	// if_walls(pars->land[pars->land_range]);
	// printf("%s\n", pars->land[pars->land_range - 1]);
	printf("VALID MAP\n");
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
	exit(0);
}