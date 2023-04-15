#include "all.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


int	*make_img(t_img *img)
{
	t_color	color;
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	printf("%x \n", color.color);
	int	x;
	int	y = 0;

	color.trgb.t = 0;
	while (y < WIN_HEIGHT)
	{
		color.trgb.g = (unsigned char)y;
		x = 0;
		while (x < WIN_WIDTH)
		{
			color.trgb.r = 255 - (unsigned char)x;
			color.trgb.b = (unsigned char)(x * y / 255);
			my_mlx_pixel_put(img, x, y, color.color);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}



// gradation!!
// int	*make_img(t_img *img)
// {
// 	t_color	color;
// 	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
// 	printf("%x \n", color.color);
// 	int	x;
// 	int	y = 0;

// 	color.trgb.t = 0;
// 	while (y < WIN_HEIGHT)
// 	{
// 		color.trgb.g = (unsigned char)y;
// 		x = 0;
// 		while (x < WIN_WIDTH)
// 		{
// 			color.trgb.r = 255 - (unsigned char)x;
// 			color.trgb.b = (unsigned char)(x * y / 255);
// 			my_mlx_pixel_put(img, x, y, color.color);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (SUCCESS);
// }
