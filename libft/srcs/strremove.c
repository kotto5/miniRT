/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strremove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:42:40 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/29 19:42:40 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_copied_removed_str(\
	char *str, const char *substr, size_t len_substr, size_t cnt_substr\
)
{
	char	*removed_str;
	size_t	i_str;
	size_t	i_removed_str;
	int		result_strncmp;

	removed_str = (char *)malloc(sizeof(char) \
		* (ft_strlen_s(str) - (len_substr * cnt_substr) + 1));
	i_str = 0;
	i_removed_str = 0;
	while (1)
	{
		result_strncmp = ft_strncmp(&str[i_str], substr, len_substr);
		while (result_strncmp == 0)
		{
			i_str += len_substr;
			result_strncmp = ft_strncmp(&str[i_str], substr, len_substr);
		}
		if (str[i_str] == '\0')
			break ;
		removed_str[i_removed_str] = str[i_str];
		i_str++;
		i_removed_str++;
	}
	removed_str[i_removed_str] = '\0';
	return (removed_str);
}

char	*strremove(char *str, const char *substr)
{
	char	*addrr_substr;
	size_t	len_substr;
	size_t	cnt_substr;

	if (str == NULL)
		return (NULL);
	if (substr == NULL || substr[0] == '\0')
		return (ft_strdup_s(str));
	if (ft_strcmp_s(str, substr) == 0)
		return (ft_strdup_s(""));
	len_substr = ft_strlen_s(substr);
	cnt_substr = 0;
	addrr_substr = str;
	while (1)
	{
		addrr_substr = ft_strnstr(addrr_substr, substr, len_substr);
		if (addrr_substr == NULL)
			break ;
		cnt_substr++;
	}
	return (get_copied_removed_str(str, substr, len_substr, cnt_substr));
}

char	*strremove_free(char *str, const char *substr)
{
	char	*removed_str;

	removed_str = strremove(str, substr);
	free(str);
	return (removed_str);
}
