/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:26 by yichiba           #+#    #+#             */
/*   Updated: 2023/09/14 15:15:09 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	s = (char *)malloc(count * size);
	if (!s)
		return (NULL);
	while (i < (count * size))
	{
		s[i] = 0;
		i++;
	}
	return (s);
}

t_ray	*ft_lstnew(int indice)
{
	t_ray	*node;

	node = (t_ray *)ft_calloc(1, sizeof(t_ray));
	if (!node)
		return (NULL);
	node->indice = indice;
	node->angle = -1;
	node->len = -1;
	node->x = -1;
	node->y = -1;
	node->dir = -1;
	return (node);
}
