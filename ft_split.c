#include "cub3D.h"

static size_t	count_strings(const char *str, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && str[i] != c)
			i++;
	}
	return (count);
}

static size_t	check_len_of_word(const char *str, char c)
{
	size_t	a;

	a = 0;
	while (str[a] != '\0' && str[a] != c)
		a++;
	return (a);
}

static char	*fill_string(const char *str, char c)
{
	char	*word;
	size_t	a;
	size_t	lenword;

	a = 0;
	lenword = check_len_of_word(str, c);
	word = (char *)malloc(sizeof(char) * (lenword + 1));
	if (!word)
		return (NULL);
	while (a < lenword)
	{
		word[a] = str[a];
		a++;
	}
	word[a] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char		**strings;
	size_t		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	strings = (char **)malloc(sizeof(char *) * (count_strings(s, c) + 1));
	if (!strings)
		return (NULL);
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0')
		{
			strings[i] = fill_string(s, c);
			if (!strings[i])
				return (NULL);
			i++;
		}
		while (*s != '\0' && *s != c)
			s++;
	}
	strings[i] = 0;
	return (strings);
}