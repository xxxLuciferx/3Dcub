/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:40:50 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/30 18:02:18 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	checking_data(t_pars *pars)
{
	int i;

	i = 0;
	if_directions_and_colors_exist(pars->map);
	// for (size_t i = 0; pars->map[i]; i++)
	// {
	// 	printf("%s\n", pars->map[i]);
	// }
	
	// exit(0);
	while (pars->map[i])
	{
		collect_texture_and_colors(pars, i);
		if(check_pars(pars))
		{
			i++;
			break;
		}
		i++;
	}
	ft_map_copy(pars, i);
	left_wall(pars);
	if_line_of_walls(pars->land[0]);
	if_line_of_walls(pars->land[pars->land_range]);
	if_valid_inside_lines(pars);
}
void	map_lines(char *buffer, int pos)
{
	int i;

	i = 0;
	while (pos && buffer[0] != '\n')
	{
		if(buffer[pos] == '\n' && buffer[pos - 1] == '\n')
			error_map();
		pos--;
	}
}

int	first_in_map(char *buffer, int pos)
{
	int number = 0;
	while (pos && buffer[pos])
	{
		if(buffer[pos] == '1' && buffer[pos - 1] == '\n')
			number = pos;
		pos--;
	}
	return (number);
}
void	check_new_lines(char *buffer,int start, int end)
{
	while (start <= end)
	{
		if(buffer[start] == '\n' && buffer[start + 1] == '\n')
				error_map();
		start++;
	}
}
int	last_char_pos(char *line, int last_pos)
{
	while (last_pos)
	{
		if(line[last_pos] == ' ' || line[last_pos] == '\t')
			last_pos--;
		else if(line[last_pos] == '1')
			return (last_pos);
		else
			error_map();
	}
	return (last_pos);
}

