/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:46:52 by khaimer           #+#    #+#             */
/*   Updated: 2023/09/14 19:58:27 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(char **land)
{
	int	i;

	i = 0;
	while (land[i])
	{
		free(land[i]);
		i++;
	}
	free(land);
}

void	free_all(t_tools *tools)
{
	(void)tools;
	exit(1);
}

void	file_not_found(t_tools *tools)
{
	(void)tools;
	printf("Error\nFile not found\n");
	exit(1);
}
