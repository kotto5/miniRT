/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:50:29 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/29 19:03:46 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void	*get_identifer_info(char **split, size_t index)
{
	static void *(*const get_func[])(char **split) \
		= {get_ambient_lignt, \
			get_camera, \
			get_light_node, \
			get_sphere_node, \
			get_plane_node, \
			get_cylinder_node, \
			get_cone_node};
	if (index >= sizeof(get_func) / sizeof(void *))
		return (NULL);
	else
		return (get_func[index](split));
}

static bool	is_valid_identifer(char *input, size_t *index)
{
	static const char	*identifers[] = {\
		"A", "C", "L", "sp", "pl", "cy", "cn"\
	};
	size_t				i;

	i = 0;
	while (i < sizeof(identifers) / sizeof(char *))
	{
		if (ft_strncmp(input, identifers[i], ft_strlen(identifers[i]) + 1) \
			== 0)
		{
			*index = i;
			return (true);
		}
		i++;
	}
	return (false);
}

static int	set_instance(t_env *env, size_t index, void *ret)
{
	if (index == 0)
		env->am_light = ret;
	else if (index == 1)
		env->camera = ret;
	else if (index < 3)
		ft_dlstadd_back(&env->light_list, ret);
	else
		ft_dlstadd_back(&env->obj_list, ret);
	return (0);
}

static bool	is_empty_line(char **split)
{
	if (split[0] == NULL)
	{
		free (split);
		return (true);
	}
	return (false);
}

int	parse_line(char *line, t_env *env)
{
	size_t	index;
	char	**split;
	void	*ret;
	bool	is_valid;

	split = ft_split(line, ' ');
	if (split == NULL)
		return (ERROR);
	if (is_empty_line(split))
		return (SUCCESS);
	is_valid = is_valid_identifer(split[0], &index);
	if (is_valid)
		ret = get_identifer_info(split, index);
	free_double_ptr(split);
	if (is_valid == false || ret == NULL)
		return (ERROR);
	if (gc_add(ret) == false)
	{
		free (ret);
		return (ERROR);
	}
	set_instance(env, index, ret);
	return (SUCCESS);
}

// 全ての要素は改行で区切る
// 空行は許されるが、何も文字は許されない
// 全ての要素の先頭はidentifer である
// identifer それぞれに、必要な項目がある。
// 任意の数のスペースは項目を区切る。
// 複数の数字を含む項目は、カンマで区切られる。
// A, C identiferは必須
