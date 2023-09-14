/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:50:07 by khaimer           #+#    #+#             */
/*   Updated: 2023/09/14 15:16:52 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strchr(const char *str, int c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < (len + 1))
	{
		if (str[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	slen;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	i = 0;
	if (!len || !slen || start >= slen)
	{
		dst = (char *)malloc(sizeof(char));
		dst[0] = '\0';
		return (dst);
	}
	while (i < len && s[i + start] != '\0')
		i++;
	dst = (char *)malloc((i + 1));
	if (!dst)
		return (NULL);
	j = 0;
	while (j < i)
		dst[j++] = s[start++];
	dst[j] = '\0';
	return (dst);
}

static size_t	count_words(const char *str, char *c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_strchr(c, str[i]) >= 0)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] && ft_strchr(c, str[i]) == -1)
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char *c)
{
	char	**split;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s)
		return (NULL);
	split = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	start = 0;
	end = 0;
	i = -1;
	while (++i < count_words(s, c))
	{
		while (ft_strchr(c, s[start]) >= 0)
			start++;
		end = start;
		while (ft_strchr(c, s[end]) == -1 && s[end])
			end++;
		split[i] = ft_substr(s, start, (end - start));
		start = end;
	}
	split[i] = 0;
	return (split);
}
