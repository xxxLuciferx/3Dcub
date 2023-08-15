/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:24:25 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/15 12:32:26 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	error_player(void)
{
	printf("\n$ Invalid PLAYER numbers\n\n");
	exit(0);
}
void	error_map(void)
{
	printf("\n$ Invalid MAP format\n\n");
	while (1);
	exit(1);
}
void	error_colors(void)
{
	printf("\n$ Incorrect MAP colors\n\n");
	exit(1);
}
void	error_path(void)
{
	printf("\n$ Incorrect path\n\n");
	exit(1);
}
