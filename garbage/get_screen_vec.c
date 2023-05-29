// t_vec3	get_screen_vec(int x, int y, t_vec3 eye_position)
// {
// 	double	win_x;
// 	double	win_y;
// 	double	win_z;
// 	double	width;
// 	double	height;
// 	double	ord;

// 	width = (double)WIN_WIDTH;
// 	height = (double)WIN_HEIGHT;
// 	ord = (double)WIN_ORD;
// 	win_x = (double)x / (ord / 2.0) - width / ord + eye.pos.x;
// 	win_y = height / ord - (double)y / (ord / 2.0) + eye.pos.y;
// 	win_z = eye.pos.z + eye.distance_to_window;
// 	print_vec(eye.orientation, "win_x is");
// 	win_x = (double)x / (ord / 2.0) - width / ord + eye.pos.x + eye.orientation.x;
// 	win_y = height / ord - (double)y / (ord / 2.0) + eye.pos.y + eye.orientation.y;
// 	win_z = eye.pos.z + eye.distance_to_window + eye.orientation.z;
// 	return (get_vec(win_x, win_y, win_z));
// }