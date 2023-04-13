#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

#define WIN_WIDTH 500
#define WIN_HEIGHT 500

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	void *mlx;
	void *win;
	int x = 0;
	int y = 0;
	
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");

}