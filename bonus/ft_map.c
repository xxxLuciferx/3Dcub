/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:15:18 by khaimer           #+#    #+#             */
/*   Updated: 2023/09/14 19:59:23 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_pars(t_pars *pars)
{
	if (pars->east_path == NULL || pars->north_path == NULL || \
	pars->south_path == NULL || pars->west_path == NULL || pars->c_b == \
	-1 || pars->c_g == -1 || pars->c_r == -1 || pars->f_b == -1 \
	|| pars->f_g == -1 || pars->f_r == -1)
		return (0);
	return (1);
}

void	if_directions_and_colors_exist(t_pars *pars)
{
	int	i;
	int	j;
	int	data;

	i = 0;
	data = 0;
	while (pars->map[i])
	{
		j = 0;
		while (pars->map[i][j] == ' ' || pars->map[i][j] == '\t')
			j++;
		if (pars->map[i][j] == 'N' || pars->map[i][j] == 'S'
			|| pars->map[i][j] == 'W' || pars->map[i][j] == 'E'
			|| pars->map[i][j] == 'F' || pars->map[i][j] == 'C')
			data++;
		else if (pars->map[i][j] != '\n' && pars->map[i][j] != '1')
			error_map();
		i++;
	}
	if (data != 6)
		error_map();
}

void	reading_map(t_tools *tools, char *av)
{
	int		fd;
	int		i;
	char	buffer[READER];

	i = 0;
	tools->pars = malloc(sizeof(t_pars));
	initiation(tools);
	fd = open(av, O_RDONLY, NULL);
	i = read(fd, buffer, READER - 1);
	if (i <= 0)
		error_file(tools);
	buffer[i] = '\0';
	i = last_char_pos(tools, buffer, i - 1);
	check_new_lines(tools, buffer, first_in_map(buffer, i), i);
	tools->pars->map = ft_split(buffer, "\n");
	checking_data(tools->pars);
}

void	valid_entry(int ac, char **av, t_tools *tools)
{
	int	len;

	if (ac != 2)
	{
		printf("\n$ Invalid arguments\n\n");
		exit(1);
	}
	len = ft_strlen(av[1]);
	if (len < 4 || av[1][len - 1] != 'b' || av[1][len - 2] != 'u' || av[1][len
		- 3] != 'c' || av[1][len - 4] != '.')
	{
		printf("\n$ Please enter a .cub file\n\n");
		exit(1);
	}
	reading_map(tools, av[1]);
}
