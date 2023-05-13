
// int	main()
// {
// 	t_intersection	intersection;
// 	t_ray	ray;
	// t_obj	*obj;
	// t_rect	*rect;
// 	t_dlist	*gb_list;

// gb_list = NULL;
// rect = make_rect_instance(get_vec(2,2,2), get_vec(6, 8, 6), &gb_list);
// obj = new_obj(O_RECT, get_t_refrect(b_color_get(0,0,0,0), b_color_get(0, 1,1,0), b_color_get(0,0,1,0), 5, false, (t_bright_color){1.0, 1.0, 1.0, 1.0}),
// rect, &gb_list);

// 	// intersection = get_intersection_rect(ray, obj);

// 	// if (intersection.does_intersect)
// 	// {
// 	// 	printf("1======OK======!\n");
// 	// 	// print_vec(intersection.position, "pos");
// 	// 	// print_vec(intersection.vertical_dir, "dir");
// 	// }
// 	// else
// 	// 	printf("1=====NO======!\n");

// 	ray.pos = (t_vec3){0,0,10};ray.dir = (t_vec3){0,0,1};rect->bound1 = get_vec(2,2,2);rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");


// // 入ってて前向き
// 	ray.pos = (t_vec3){0,0,0}; ray.dir = (t_vec3){0,0,1}; rect->bound1 = get_vec(-2,-2,-2); rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");

// // 入ってて後ろ向き
// // ray.pos = (t_vec3){5,5,5}; ray.dir = (t_vec3){0,0,-1}; rect->bound1 = get_vec(2,2,2); rect->bound2 = get_vec(6, 8, 6);
// ray.pos = (t_vec3){0,0,0}; ray.dir = (t_vec3){0,0,-1}; rect->bound1 = get_vec(-2,-2,-2); rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");

// // 視点をちょっと前
// ray.pos = (t_vec3){1,1,1}; ray.dir = (t_vec3){0,0,-1}; rect->bound1 = get_vec(-2,-2,-2); rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("視点をちょっと前======OK======!\n");
// 	else
// 		printf("視点をちょっと前=====NO======!\n");

// // ぎり入ってる
// ray.pos = (t_vec3){3,3,3}; ray.dir = (t_vec3){0,0,-1}; rect->bound1 = get_vec(0,0,0); rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("ぎり入ってる======OK======!\n");
// 	else
// 		printf("ぎり入ってる=====NO======!\n");

// // ぎり入ってる
// ray.pos = (t_vec3){3,3,3}; ray.dir = (t_vec3){0,0,-1}; rect->bound1 = get_vec(0.9,0.9,0.9); rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("ぎりてすと======OK======!\n");
// 	else
// 		printf("ぎりてすと=====NO======!\n");

// // なぞ
// ray.pos = (t_vec3){5,5,5}; ray.dir = (t_vec3){0,0,-1}; rect->bound1 = get_vec(2,2,2); rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("なぞ======OK======!\n");
// 	else
// 		printf("なぞ=====NO======!\n");


// ray.pos = (t_vec3){0,0,10}; ray.dir = (t_vec3){0,1,0}; rect->bound1 = get_vec(2,2,2); rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");

// ray.pos = (t_vec3){0,0,10}; ray.dir = (t_vec3){1,0,0}; rect->bound1 = get_vec(2,2,2); rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");






// ray.pos = (t_vec3){0,0,10}; ray.dir = (t_vec3){1,0,0}; rect->bound1 = get_vec(-2,-2,-2); rect->bound2 = get_vec(-1,1,1);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("333333======OK======!\n");
// 	else
// 		printf("333333=====NO======!\n");

// ray.pos = (t_vec3){0,0,10}; ray.dir = (t_vec3){1,0,0}; rect->bound1 = get_vec(-2,-2,-2); rect->bound2 = get_vec(-1,-1,1);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");

// ray.pos = (t_vec3){0,0,10}; ray.dir = (t_vec3){1,0,0}; rect->bound1 = get_vec(-2,-2,-2); rect->bound2 = get_vec(-3,-3,-3);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");

// ray.pos = (t_vec3){0,0,10}; ray.dir = (t_vec3){1,0,0}; rect->bound1 = get_vec(-2,-2,-2); rect->bound2 = get_vec(-3,1,1);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");

// ray.pos = (t_vec3){0,0,10}; ray.dir = (t_vec3){1,0,0}; rect->bound1 = get_vec(-2,-2,-2); rect->bound2 = get_vec(-3,-3,-3);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");
// }

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q miniRT");
// }
