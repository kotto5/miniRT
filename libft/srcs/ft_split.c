/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:51:38 by kakiba            #+#    #+#             */
/*   Updated: 2022/07/27 15:57:37 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_split(const char *s, char c);
static size_t	check_split(char **nptr, char const *s, size_t i, size_t *end);
static void		create_split(char **nptr, char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**nptr;

	if (s == NULL)
		return (NULL);
	nptr = ft_calloc(sizeof(char **), (count_split(s, c) + 1));
	if (nptr == NULL)
		return (NULL);
	create_split(nptr, s, c);
	return (nptr);
}

static void	create_split(char **nptr, char const *s, char c)
{
	size_t	i;
	size_t	end;
	size_t	start;

	i = 0;
	start = 0;
	while (s[start])
	{
		while (s[start] == c)
			++start;
		if (s[start] && ft_strchr(&s[start], c) == NULL)
		{
			end = ft_strlen(s);
			nptr[i] = ft_substr(s, start, ft_strlen(s) - start);
			start = check_split(nptr, s, i++, &end);
		}
		else if (s[start])
		{
			end = ft_strchr(&s[start], c) - s;
			nptr[i] = ft_substr(s, start, end - start);
			start = check_split(nptr, s, i++, &end);
		}
	}
	if (nptr[i - 1] != NULL)
		nptr[i] = 0;
}

static size_t	check_split(char **nptr, char const *s, size_t i, size_t *end)
{
	if (nptr[i] == NULL)
	{	
		while (i)
		{
			free(nptr[i]);
			nptr[i--] = NULL;
		}
		free(nptr[i]);
		nptr[i] = NULL;
		free(nptr);
		nptr = NULL;
		*end = ft_strlen(s);
	}
	return (*end);
}

static size_t	count_split(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] == c)
			j++;
		if (s[j])
			i++;
		while (s[j] != c && s[j])
			j++;
	}
	return (i);
}
/*
int	main()
{
	printf("%s\n", ft_split("akiba,,kyo,,suke", ',')[0]);
	printf("%s\n", ft_split(",,,,akiba,,kyo,,suke,,,", ',')[0]);
}*/
