#include "cub3D.h"
#include <math.h>
#define _USE_MATH_DEFINES

static void	my_mlx_pixel_put(t_mlx_img *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = data->buffer + (y * data->sl + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

static unsigned int	my_mlx_pixel_get(t_mlx_img *data, int x, int y)
{
	char	*src;

	src = data->buffer + (y * data->sl + x * (data->bpp / 8));
	return (*(unsigned int *)src);
}

static t_mlx_img	*get_wall_img(t_card card)
{
	if (card == nord)
		return (&g_cube.curr_map.n_wall);
	else if (card == south)
		return (&g_cube.curr_map.s_wall);
	else if (card == east)
		return (&g_cube.curr_map.e_wall);
	else if (card == west)
		return (&g_cube.curr_map.w_wall);
	else
		return (NULL);
}

static int	get_wall_size(t_vect pos, t_vect *ray)
{
	float	real_x;
	float	real_y;
	double	fraction;

	real_x = pos.x - g_cube.curr_map.p_pos.x;
	real_y = pos.y - g_cube.curr_map.p_pos.y;
	fraction = sqrtf((real_x * real_x + real_y * real_y) \
		/ (ray->x * ray->x + ray->y * ray->y));
	return ((int)((float)RES_W / (2.5 * fraction * tan(M_PI / 6))));
}

void	put_coloumn_wall(t_vect *ray, t_vect pos, t_card card, int coloumn)
{
	int			wall_size;
	int			i;
	int			wall_coloumn;
	int			wall_line;
	t_mlx_img	*mlx_img;

	mlx_img = get_wall_img(card);
	if (!mlx_img)
		return ;
	wall_size = get_wall_size(pos, ray);
	if (pos.x - floorf(pos.x) < pos.y - floorf(pos.y))
		wall_coloumn = (pos.y - floorf(pos.y)) * mlx_img->img_width;
	else
		wall_coloumn = (pos.x - floorf(pos.x)) * mlx_img->img_width;
	i = (RES_H / 2) - (wall_size / 2);
	while (i < (RES_H / 2) + (wall_size / 2))
	{
		wall_line = (int)((float)(i - ((RES_H / 2) - (wall_size / 2)))
				*((float)mlx_img->img_height / (float)wall_size));
		if (i < RES_H && i > 0 && wall_coloumn < mlx_img->img_width
			&& wall_line < mlx_img->img_height)
			my_mlx_pixel_put(&(g_cube.rcimg), coloumn, i,
				my_mlx_pixel_get(mlx_img, wall_coloumn, wall_line));
		i++;
	}
}
