/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:16:14 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/22 16:01:52 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int ft_isspace(int c)
{
    return (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\v');
}

char	*get_addrr_before_space(char *str)
{
	size_t	i_str;

	if (str == NULL)
		return (NULL);
	i_str = 0;
	while (str[i_str] != '\0')
	{
		if (ft_isspace(str[i_str]) == 1)
			return (&str[i_str]);
		i_str++;
	}
	return (NULL);
}