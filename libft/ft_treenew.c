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
	while (node && label[i_label + 1])
	{
		if (label[i_label] == 'l')
			node = node->left;
		else if (label[i_label] == 'r')
			node = node->right;
		else
			return (false);
		i_label++;
	}
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

// int	print_node(t_dtree *node, size_t level)
// {
// 	if (!node)
// 		return (0);
// 	for (size_t i = 0; i < level; i++)
// 		printf(i == level - 1 ? "|-" : "  ");
// 	printf("%d\n", *(int *)(node->content));
// 	print_node(node->left, level + 1);
// 	print_node(node->right, level + 1);
// 	return (0);
// }

int    print_node(t_dtree *node, size_t level, int c)
{
    size_t    i_level;

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
