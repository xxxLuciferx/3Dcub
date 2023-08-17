/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:39:18 by khaimer           #+#    #+#             */
/*   Updated: 2023/08/17 08:45:02 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;

	i = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		sub = (char *)malloc((ft_strlen(s) - start) + 1);
	else
		sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	while (len && s && start < ft_strlen(s))
	{
		sub[i] = s[start];
		i++;
		start++;
		len--;
	}
	sub[i] = '\0';
	return (sub);
}

static int	char_finder(const char s, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

static int	f_front(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (s1)
	{
		if (char_finder(s1[i], set))
			i++;
		else
			break ;
	}
	return (i);
}

static int	f_back(const char *s1, const char *set)
{
	int	len;

	len = (ft_strlen(s1)-1);
	while (s1[len])
	{
		if (char_finder(s1[len], set))
			len--;
		else
			break ;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		back;
	int		space;
	char	*string;

	if (!s1)
		return (NULL);
	start = f_front(s1, set);
	if (!s1[start])
		return (ft_strdup(""));
	back = f_back(s1, set);
	start = f_front(s1, set);
	space = (back - start) + 1;
	string = ft_substr2(s1, start, space);
	return (string);
}