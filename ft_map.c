/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:15:18 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/30 18:18:33 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		check_pars(t_pars *pars)
{
	if(pars->east_path == NULL || pars->north_path == NULL || pars->south_path == NULL || pars->west_path == NULL || pars->C_B == -1 || pars->C_G == -1 || pars->C_R == -1 || pars->F_B == -1 || pars->F_G == -1 || pars->F_R == -1)
		return(0);
	return(1);
}

void	if_directions_and_colors_exist(char **map)
{
	int i;
	int j;
	int	data;

	i = 0;
	data = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ' || map[i][j] == '\t')
			j++;
		if(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'F' || map[i][j] == 'C')
			data++;
		i++;
	}
	if(data != 6)
		error_map();
}

void	reading_map(t_tools *tools, char *av)
{
	int		fd;
	int		i;
	char	buffer[2001];

	i = 0;
	tools->pars = malloc(sizeof(t_pars));
	initiation(tools);
	fd = open(av, O_RDONLY, NULL);
	i = read(fd, buffer, 2000);
	if(i <= 0)
		error_file();
	buffer[i] = '\0';
	i = last_char_pos(buffer, i - 1);
	check_new_lines(buffer, first_in_map(buffer, i), i);
	tools->pars->map = ft_split(buffer, "\n");
	checking_data(tools->pars);

}

void	valid_entry(int ac, char **av, t_tools *tools)
{
	int	len;
	
	if(ac != 2)
	{
		printf("\n$ Invalid arguments\n\n");
		exit(1);
	}
	len = ft_strlen(av[1]);
	if(len < 4 || av[1][len - 1] != 'b' || av[1][len - 2] != 'u' || av[1][len - 3] != 'c' || av[1][len - 4] != '.')
	{
		printf("\n$ Please enter a .cub file\n\n");
		exit(1);
	}
	reading_map(tools, av[1]);

}