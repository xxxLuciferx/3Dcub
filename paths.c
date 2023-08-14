/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:14:58 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/14 12:28:24 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	if_valid_texture(char *texture) /// REMEMBER THIS
{
	int	i;

	i = 2;
	// printf(">>>> if_valid_texture >> %s\n", texture);
	if(texture[0] != '.' || texture[1] != '/')
		error_path();
	while (texture[i])
	{
		if(texture[i] >= 9 && texture[i] <= 13)
			error_path();
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if(s1 && s2)
	{
		while (s1[i] != '\0')
		{
			if(s1[i] != s2[i])
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

void	north_path(t_pars *pars, int i)
{
	char	**tmp;
	// char	spliter;
	
	// spliter = find_spliter(pars->map[i]);
	
	tmp = ft_split(pars->map[i], " 	\n");
	if(ft_strcmp(tmp[0], "NO") == 0 || tmp[2] != NULL)
		error_path();
	pars->north_path = ft_strdup(tmp[1]);
	free_arrays(tmp);
	if_valid_texture(pars->north_path);
}

void	south_path(t_pars *pars, int i)
{
	char	**tmp;
	// char	spliter;
	
	// spliter = find_spliter(pars->map[i]);	
	tmp = ft_split(pars->map[i], " 	\n");
	if(ft_strcmp(tmp[0], "SO") == 0 || tmp[2] != NULL)
		error_path();
	pars->south_path = ft_strdup(tmp[1]);
	free_arrays(tmp);
}
void	west_path(t_pars *pars, int i)
{
	char	**tmp;
	// char	spliter;

	// spliter = find_spliter(pars->map[i]);
	tmp = ft_split(pars->map[i], " 	\n");
	if(ft_strcmp(tmp[0], "WE") == 0 || tmp[2] != NULL)
		error_path();
	pars->west_path = ft_strdup(tmp[1]);
	free_arrays(tmp);
}


void	east_path(t_pars *pars, int i)
{
	char	**tmp;
	// char	spliter;

	// spliter = find_spliter(pars->map[i]);
	tmp = ft_split(pars->map[i], " 	\n");
	if(ft_strcmp(tmp[0], "EA") == 0 || tmp[2] != NULL)
		error_path();
	pars->east_path = ft_strdup(tmp[1]);
	free_arrays(tmp);
}