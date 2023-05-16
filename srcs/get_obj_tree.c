#include "all.h"

t_dtree *get_obj_tree(t_env *env)
{
	(void)env;
	t_dtree	*tree;
	t_vec3	pos;
	t_obj		*obj;
	t_sphere	*sphere;
	double	average;
	t_dlist	*node;
	size_t	cnt_obj;

	tree = NULL;
	cnt_obj = 0;
	node = env->obj_list;
	average = 0;
	while (node)
	{
		obj = node->content;
		sphere = obj->instance;
		pos = sphere->pos;
		average += pos.y;
		node = node->next;
		cnt_obj++;
	}
	average /= (double)cnt_obj;
	node = env->obj_list;
	while (node)
	{
		
	}
	return (NULL);
}