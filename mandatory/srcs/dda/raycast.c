#include "cub3D.h"
#include <math.h>
#define _USE_MATH_DEFINES

void	set_cam_vect(t_vect *vect)
{
	vect->x = -g_cube.curr_map.p_dir.y;
	vect->y = g_cube.curr_map.p_dir.x;
	vect->x = (vect->x * 2) / (3 * RES_WIDTH / 2);
	vect->y = (vect->y * 2) / (3 * RES_WIDTH / 2);
}

t_card	throw_ray_x(t_vect *res, t_vect ray)
{
	double		m;
	int			x;
	double		y; 

	if (ray.x == 0.f)
		return unknown;
	if (ray.y == 0.f)
		return unknown; //other function please
	m = ray.y / ray.x;
	if (ray.x > 0)
	{
		x = (int)g_cube.curr_map.p_pos.x;
		x++;
		while (x < g_cube.curr_map.map_width)
		{
			y = m * ((double)x - g_cube.curr_map.p_pos.x) + g_cube.curr_map.p_pos.y;
			if (y < 0 || y >= g_cube.curr_map.map_height)
				return unknown;
			if (g_cube.curr_map.map[(int)y][x] == 1)
				break ;
			x++;
		}
		res->x = x;
		res->y = y;
		return west;
	}
	if (ray.x < 0)
	{
		x = (int)g_cube.curr_map.p_pos.x;
		while (x > 0 && x < g_cube.curr_map.map_width)
		{
			y = m * ((double)x - g_cube.curr_map.p_pos.x) + g_cube.curr_map.p_pos.y;
			if (y < 0 || y >= g_cube.curr_map.map_height)
				return unknown;
			else if (g_cube.curr_map.map[(int)y][x - 1] == 1)
				break;
			x--;
		}
		res->x = x;
		res->y = y;
		return (east);
	}
	return (unknown);
}

t_card	throw_ray_y(t_vect *res, t_vect ray, t_card oldcard)
{
	double		m;
	double		x;
	int			y; 

	if (ray.y == 0.f)
		return oldcard;
	if (ray.x == 0.f)
		return oldcard;
	m = ray.x / ray.y;
	if (ray.y > 0)
	{
		y = (int)g_cube.curr_map.p_pos.y;
		y++;
		while (y < g_cube.curr_map.map_height)
		{
			x = m * ((double)y - g_cube.curr_map.p_pos.y) + g_cube.curr_map.p_pos.x;
			if (x < 0 || x >= g_cube.curr_map.map_width)
				return oldcard;
			else if (g_cube.curr_map.map[y][(int)x] == 1)
				break ;
			y++;
		}
		if (res->y == 0.f || y <= res->y)
		{
			res->x = x;
			res->y = y;
			return (south);
		}
		return oldcard;
	}
	if (ray.y < 0)
	{
		y = (int)g_cube.curr_map.p_pos.y;
		while (y > 0 && y < g_cube.curr_map.map_height)
		{
			x = m * ((double)y - g_cube.curr_map.p_pos.y) + g_cube.curr_map.p_pos.x;
			if (x < 0 || x >= g_cube.curr_map.map_width) //map_height
				return oldcard;
			if (g_cube.curr_map.map[y - 1][(int)x] == 1)
				break;
			y--;
		}
		if (y > res->y)
		{
			res->x = x;
			res->y = y;
			return (nord);
		}
		return (oldcard);
	}
	return (oldcard);
}

void	put_coloumn_wall(t_vect *ray, t_vect pos, t_card card, int coloumn)
{
	double	fraction;
	int		wall_size;
	float	real_x;
	float	real_y;
	int		i;
	int		wall_coloumn;
	int		wall_line;
	t_mlx_img	*mlx_img;

	if(card == nord)
		mlx_img = &g_cube.curr_map.n_wall;
	else if (card == south)
		mlx_img = &g_cube.curr_map.s_wall;
	else if (card == east)
		mlx_img = &g_cube.curr_map.e_wall;
	else if (card == west)
		mlx_img = &g_cube.curr_map.w_wall;
	else if (card == unknown)
		return ;
	real_x = pos.x - g_cube.curr_map.p_pos.x;
	real_y = pos.y - g_cube.curr_map.p_pos.y;
	fraction = sqrtf((real_x * real_x + real_y * real_y) / (ray->x * ray->x + ray->y * ray->y));
	wall_size = (int)((float)RES_WIDTH / (2.5 * fraction * tan(M_PI / 6)));
	if (pos.x - floorf(pos.x) < pos.y - floorf(pos.y))
		wall_coloumn = (pos.y - floorf(pos.y)) * mlx_img->img_width;
	else
		wall_coloumn = (pos.x - floorf(pos.x)) * mlx_img->img_width;
	i = (RES_HEIGHT / 2) - (wall_size / 2);
	while (i < (RES_HEIGHT / 2) + (wall_size / 2))
	{
		wall_line = (int)((float)(i - ((RES_HEIGHT / 2) - (wall_size / 2))) * (float)mlx_img->img_height / (float)wall_size);
		if (i < RES_HEIGHT && i > 0 && wall_coloumn < mlx_img->img_width && wall_line < mlx_img->img_height)
			((unsigned int *)g_cube.img_onload.buffer)[i * (g_cube.img_onload.sl / 4) + coloumn] = 
				((unsigned int *)(mlx_img->buffer))[wall_line  * (mlx_img->sl / 4) + wall_coloumn];
		i++;
	}
}

// TO DeLEETTTEE
void	put_ray(t_vect w_pos, t_vect ray, int print_ray)
{
	(void)w_pos;
	t_vect p_pos_c;

	p_pos_c = g_cube.curr_map.p_pos;
	((unsigned int *)g_cube.img_onload.buffer)[(int)(w_pos.y * (float)g_cube.curr_map.n_wall.img_height) * (g_cube.img_onload.sl / 4) + (int)(w_pos.x * (float)g_cube.curr_map.n_wall.img_width)] = 0x00ff0000;
	if (!print_ray)
		return ;
	int i;
	i = 0;
	while (i < 1000)
	{
		p_pos_c.x += ray.x/100;
		p_pos_c.y += ray.y/100;
		if (p_pos_c.x >=0 && p_pos_c.x <= 9 && p_pos_c.y >= 0 && p_pos_c.y <= 9)
			((unsigned int *)g_cube.img_onload.buffer)[(int)(p_pos_c.y * (float)g_cube.curr_map.n_wall.img_height) * (g_cube.img_onload.sl / 4) + (int)(p_pos_c.x * (float)g_cube.curr_map.n_wall.img_width)] = 0x000000c6;
		i++;
	}
}

void	raycast()
{
	t_vect	wall_hit;
	t_vect	cam;
	t_vect	ray;
	t_card	card;
	int		i;

	set_cam_vect(&cam);
	i = 0;
	while (i < RES_WIDTH)
	{
		wall_hit.x = 0.f;
		wall_hit.y = 0.f;
		ray.x = g_cube.curr_map.p_dir.x + (i - RES_WIDTH / 2) * cam.x;
		ray.y = g_cube.curr_map.p_dir.y + (i - RES_WIDTH / 2) * cam.y;
		card = throw_ray_x(&wall_hit, ray);
		card = throw_ray_y(&wall_hit, ray, card);
		// if (! (i % 50))
		// 	put_ray(wall_hit, ray, 1);
		// else
		// 	put_ray(wall_hit, ray, 0);
		put_coloumn_wall(&ray, wall_hit, card, i);
		i++;
	}
}