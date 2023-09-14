/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:24:25 by khaimer           #+#    #+#             */
/*   Updated: 2023/09/14 15:13:28 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	error_player(t_tools *tools)
{
	free_map(tools->pars->land);
	free(tools->pars);
	printf("\nError\n$ Invalid PLAYER numbers\n\n");
	exit(0);
}

void	error_map(t_tools *tools)
{
	free(tools->pars);
	printf("\nError\n$ Invalid MAP format\n\n");
	exit(1);
}

void	error_colors(void)
{
	printf("\nError\n$ Incorrect MAP colors\n\n");
	exit(1);
}

void	error_path(void)
{
	printf("\nError\n$ Incorrect path\n\n");
	exit(1);
}

void	error_file(t_tools *tools)
{
	free(tools->pars);
	printf("\n$ Invalid file\n\n");
	exit(1);
}
