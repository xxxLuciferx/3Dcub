/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichiba <yichiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:10:26 by yichiba           #+#    #+#             */
/*   Updated: 2023/09/04 12:58:59 by yichiba          ###   ########.fr       */
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

// void	ft_lstadd_back(t_ray **lst, t_ray *new)
// {
// 	t_ray	*d;

// 	if (!lst || !new)
// 		return ;
// 	d = *lst;
// 	if (*lst)
// 	{
// 		while (d -> next)
// 			d = d -> next;
// 	d -> next = new;
// 	}
// 	else
// 		*lst = new;
// }

// t_ray	*ft_lstnew(t_tools *tools, float angle, int len, int indice)
// {
// 	t_ray	*node;

// 	node = (t_ray *)ft_calloc(1, sizeof(t_ray));
// 	if (!node)
// 		return (NULL);
//     node->indice = indice;
// 	node->angle = angle;
//     node->len = len;
//     node->x = tools->player_x + len * cos(angle);
//     node->y = tools->player_y + len * sin(angle);
//     node->next = NULL;
// 	return (node);
// }  

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