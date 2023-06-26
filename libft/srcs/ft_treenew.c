/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 20:32:41 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/05 20:46:21 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

t_dtree	*ft_treenew(void *content)
{
	t_dtree	*node;

	node = malloc(sizeof(t_dlist));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->root = NULL;
	node->content = content;
	node->type = DT_NODE;
	return (node);
}

static bool	ft_tree_add_loop(t_dtree *node, char *label, size_t *i_label)
{
	while (node && label[*i_label + 1])
	{
		if (label[*i_label] == 'l')
			node = node->left;
		else if (label[*i_label] == 'r')
			node = node->right;
		else
			return (false);
		(*i_label)++;
	}
	return (true);
}

bool	ft_tree_add(t_dtree **root, t_dtree *new, char *label)
{
	t_dtree	*node;
	size_t	i_label;

	if (root == NULL)
		return (false);
	if (*root == NULL)
	{
		*root = new;
		return (true);
	}
	node = *root;
	i_label = 0;
	if (ft_tree_add_loop(node, label, &i_label) == false)
		return (false);
	if (node == NULL)
		return (false);
	if (label[i_label] == 'l')
		node->left = new;
	else if (label[i_label] == 'r')
		node->right = new;
	else
		return (false);
	return (true);
}

int	print_node(t_dtree *node, size_t level, int c)
{
	size_t	i_level;

	if (!node)
		return (0);
	i_level = 0;
	while (i_level < level)
	{
		if (i_level == level - 1)
			write(1, "|-", 2);
		else
			write(1, "  ", 2);
		i_level++;
	}
	if (c == 0)
		printf("root: %d\n", *(int *)(node->content));
	else if (c == 'l')
		printf("left: %d\n", *(int *)(node->content));
	else if (c == 'r')
		printf("right: %d\n", *(int *)(node->content));
	print_node(node->left, level + 1, 'l');
	print_node(node->right, level + 1, 'r');
	return (0);
}
