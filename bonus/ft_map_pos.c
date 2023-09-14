/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:40:50 by khaimer           #+#    #+#             */
/*   Updated: 2023/09/14 19:05:39 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	checking_data(t_pars *pars)
{
	int	i;

	i = 0;
	if_directions_and_colors_exist(pars);
	while (pars->map[i])
	{
		collect_texture_and_colors(pars, i);
		if (check_pars(pars))
		{
			i++;
			break ;
		}
		i++;
	}
	ft_map_copy(pars, i);
	left_wall(pars);
	if_line_of_walls(pars, pars->land[0]);
	if_line_of_walls(pars, pars->land[pars->land_range]);
	if_valid_inside_lines(pars);
}

int	first_in_map(char *buffer, int pos)
{
	int	number;

	number = 0;
	while (pos && buffer[pos])
	{
		if (buffer[pos] == '1' && buffer[pos - 1] == '\n')
			number = pos;
		pos--;
	}
	return (number);
}

void	check_new_lines(t_tools *tools, char *buffer, int start, int end)
{
	(void)tools;
	while (start <= end)
	{
		if (buffer[start] == '\n' && buffer[start + 1] == '\n')
			error_map();
		start++;
	}
}

int	last_char_pos(t_tools *tools, char *line, int last_pos)
{
	(void)tools;
	while (last_pos)
	{
		if (line[last_pos] == ' ' || line[last_pos] == '\t')
			last_pos--;
		else if (line[last_pos] == '1')
			return (last_pos);
		else
			error_map();
	}
	return (last_pos);
}
