/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 11:41:07 by khaimer           #+#    #+#             */
/*   Updated: 2023/09/14 19:04:04 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_atoi(const char *str)
{
	int	a;
	int	sign;
	int	res;

	res = 0;
	a = 0;
	sign = 1;
	while (str[a] == ' ' || (str[a] <= 13 && str[a] >= 9) || str[a] == 'F'
		|| str[a] == 'C')
		a++;
	if (str[a] == '-')
	{
		sign = sign * -1;
		a++;
	}
	else if (str[a] == '+')
		a++;
	while ((str[a] <= '9' && str[a] >= '0'))
	{
		res = str[a] - '0' + (res * 10);
		a++;
	}
	if (str[a] != '\0')
		error_map();
	return (res * sign);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*c;
	char	*m;

	i = ft_strlen(s1);
	c = (char *)ft_calloc((i + 1), sizeof(char));
	m = c;
	if (!c)
		return (NULL);
	while (*s1)
	{
		*c = *s1;
		c++;
		s1++;
	}
	*c = '\0';
	return (m);
}

char	*ft_strddup(const char *s1, int len)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len)
		str[i++] = ' ';
	str[i] = '\0';
	return (str);
}

void	collect_direction(char c, t_pars *pars)
{
	pars->ptr->angle = 0;
	if (c == 'S')
		pars->ptr->angle = 90;
	else if (c == 'W')
		pars->ptr->angle = 180;
	else if (c == 'N')
		pars->ptr->angle = 270;
}
