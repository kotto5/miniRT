#include "all.h"

// t_dlist	*get_obj_list(t_dlist **gb_list)
// {
// 	t_dlist			*obj_list;

// 	obj_list = NULL;

// 	// ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_CIRCLE, get_t_refrect(b_color_get(0, 0.1, 0.1, 0.1), b_color_get(0.0, 0.0, 0.69, 0.0), b_color_get(0, 0.30, 0.30, 0.30), 0, false, (t_bright_color){0, 0, 0, 0}),
// 	// 	make_circle_instance(get_vec(0, 1, 10), 1, gb_list), gb_list)));

// 	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_CIRCLE, get_t_refrect(b_color_get(0, 0.1, 0.1, 0.1), b_color_get(0.0, 0.0, 0.69, 0.0), b_color_get(0, 0.30, 0.30, 0.30), 5, true, (t_bright_color){0.5, 0.5, 0.5, 0.5}),
// 		make_circle_instance(get_vec(0, 1, 10), 1, gb_list), gb_list)));

// 	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_CIRCLE, get_t_refrect(b_color_get(0, 0.1, 0.1, 0.1), b_color_get(0.0, 0.0, 0.0, 0.69), b_color_get(0, 0.30, 0.30, 0.30), 0, false, (t_bright_color){0, 0, 0, 0}),
// 		make_circle_instance(get_vec(1, 1, 15), 1, gb_list), gb_list)));

// 	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_CIRCLE, get_t_refrect(b_color_get(0, 0.1, 0.1, 0.1), b_color_get(0.0, 0.0, 0.69, 0.69), b_color_get(0, 0.30, 0.30, 0.30), 1, false, (t_bright_color){0, 0, 0, 0}),
// 		make_circle_instance(get_vec(2, 1, 20), 1, gb_list), gb_list)));

// 	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_CIRCLE, get_t_refrect(b_color_get(0, 0.1, 0.1, 0.1), b_color_get(0.0, 0.69, 0.0, 0.69), b_color_get(0, 0.30, 0.30, 0.30), 1, false, (t_bright_color){0, 0, 0, 0}),
// 		make_circle_instance(get_vec(3, 1, 25), 1, gb_list), gb_list)));

// 	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_CIRCLE, get_t_refrect(b_color_get(0, 0.1, 0.1, 0.1), b_color_get(0.0, 0.69, 0.0, 0.0), b_color_get(0, 0.30, 0.30, 0.30), 0, false, (t_bright_color){0, 0, 0, 0}),
// 		make_circle_instance(get_vec(-1, 1, 5), 1, gb_list), gb_list)));

// // wall
// 	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_PLANE, get_t_refrect(b_color_get(0, 0.0, 0.8, 0.0), b_color_get(0, 0.0, 0.8, 0.0), b_color_get(0, 0.0, 0.8, 0.0), 1, false, (t_bright_color){0, 0, 0, 0}),
// 		make_plane_instance(vec_normilize(get_vec(0, 1, 0)), get_vec(0, 0, 0),  gb_list), gb_list)));

// 	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_PLANE, get_t_refrect(b_color_get(0, 0.0, 0.8, 0.0), b_color_get(0, 0.0, 0.8, 0.0), b_color_get(0, 0.0, 0.8, 0.0), 1, false, (t_bright_color){0, 0, 0, 0}),
// 		make_plane_instance(vec_normilize(get_vec(0, 1, 0)), get_vec(0, 10, 0),  gb_list), gb_list)));

// 	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_PLANE, get_t_refrect(b_color_get(0, 0.8, 0.0, 0.0), b_color_get(0, 0.8, 0.0, 0.0), b_color_get(0, 0.8, 0.0, 0.0), 1, false, (t_bright_color){0, 0, 0, 0}),
// 		make_plane_instance(vec_normilize(get_vec(1, 0, 0)), get_vec(-6, 0, 0),  gb_list), gb_list)));

// 	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_PLANE, get_t_refrect(b_color_get(0, 0.8, 0.0, 0.0), b_color_get(0, 0.8, 0.0, 0.0), b_color_get(0, 0.8, 0.0, 0.0), 1, false, (t_bright_color){0, 0, 0, 0}),
// 		make_plane_instance(vec_normilize(get_vec(1, 0, 0)), get_vec(6, 0, 0),  gb_list), gb_list)));

// 	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_PLANE, get_t_refrect(b_color_get(0, 0.0, 0.0, 0.8), b_color_get(0, 0.0, 0.0, 0.8), b_color_get(0, 0.0, 0.0, 0.8), 1, false, (t_bright_color){0, 0, 0, 0}),
// 		make_plane_instance(vec_normilize(get_vec(0, 0, 1)), get_vec(0, 0, 40),  gb_list), gb_list)));

// 	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_PLANE, get_t_refrect(b_color_get(0, 0.0, 0.0, 0.8), b_color_get(0, 0.0, 0.0, 0.8), b_color_get(0, 0.0, 0.0, 0.8), 1, false, (t_bright_color){0, 0, 0, 0}),
// 		make_plane_instance(vec_normilize(get_vec(0, 0, 1)), get_vec(0, 0, -40),  gb_list), gb_list)));

// // 	ft_dlstadd_back(&obj_list, ft_dlstnew(circle3));
// // 	ft_dlstadd_back(&obj_list, ft_dlstnew(circle3));
// 	return (obj_list);
// }


t_dlist	*get_obj_list(t_dlist **gb_list)
{
	t_dlist			*obj_list;

	obj_list = NULL;

	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_CIRCLE, get_t_refrect(b_color_get(0, 0, 0, 0), b_color_get(0, 0, 0, 0.0), b_color_get(0, 0, 0, 0), 5, true, (t_bright_color){1.0, 1.0, 1.0, 1.0}),
		make_circle_instance(get_vec(-0.25, -0.5, 3), 0.5, gb_list), gb_list)));

	// ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_CIRCLE, get_t_refrect(b_color_get(0,0.2,0.4,0.6), b_color_get(0,0.2,0.4,0.6), b_color_get(0,0.2,0.4,0.6), 5, false, (t_bright_color){0,0,0,0}),
	// 	make_circle_instance(get_vec(-0.25, -0.5, 3), 0.5, gb_list), gb_list)));

// wall
// 床と天井の法線ベクトル　が、なんかおかしいかも？
	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_PLANE, get_t_refrect(b_color_get(0, 0.0, 0.0, 0.0), b_color_get(0.0, 1, 1, 1), b_color_get(0, 0.0, 0.0, 0.0), 1, false, (t_bright_color){0, 0, 0, 0}),
		make_plane_instance(vec_normilize(get_vec(0, 1, 0)), get_vec(0, -1, 0),  gb_list), gb_list)));

	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_PLANE, get_t_refrect(b_color_get(0, 0.0, 0.0, 0.0), b_color_get(0.0, 1, 1, 1), b_color_get(0, 0.0, 0.0, 0.0), 1, false, (t_bright_color){0, 0, 0, 0}),
		make_plane_instance(vec_normilize(get_vec(0, -1, 0)), get_vec(0, 1, 0),  gb_list), gb_list)));

	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_PLANE, get_t_refrect(b_color_get(0, 0.0, 0.0, 0.0), b_color_get(0.0, 0, 1, 0), b_color_get(0, 0.0, 0.0, 0.0), 1, false, (t_bright_color){0, 0, 0, 0}),
		make_plane_instance(vec_normilize(get_vec(-1, 0, 0)), get_vec(1, 0, 0),  gb_list), gb_list)));

	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_PLANE, get_t_refrect(b_color_get(0, 0.0, 0.0, 0.0), b_color_get(0.0, 1, 0, 0), b_color_get(0, 0.0, 0.0, 0.0), 1, false, (t_bright_color){0, 0, 0, 0}),
		make_plane_instance(vec_normilize(get_vec(1, 0, 0)), get_vec(-1, 0, 0),  gb_list), gb_list)));

	ft_dlstadd_back(&obj_list, ft_dlstnew(new_obj(O_PLANE, get_t_refrect(b_color_get(0, 0.0, 0.0, 0.0), b_color_get(0.0, 1, 1, 1), b_color_get(0, 0.0, 0.0, 0.0), 1, false, (t_bright_color){0, 0, 0, 0}),
		make_plane_instance(vec_normilize(get_vec(0, 0, -1)), get_vec(0, 0, 5),  gb_list), gb_list)));


// 	ft_dlstadd_back(&obj_list, ft_dlstnew(circle3));
// 	ft_dlstadd_back(&obj_list, ft_dlstnew(circle3));
	return (obj_list);
}
