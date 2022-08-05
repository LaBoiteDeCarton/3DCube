#include "cub3D.h"
#include <math.h>
#define _USE_MATH_DEFINES

static t_card	throw_ray_x_left(t_vect *res, t_vect ray)
{
	float	m;
	float	x;
	float	y;

	if (ray.x >= 0.f || ray.y == 0.f)
		return (unknown);
	m = ray.y / ray.x;
	x = (int)g_cube.curr_map.p_pos.x;
	while (x > 0 && x < g_cube.curr_map.map_width)
	{
		y = m * (x - g_cube.curr_map.p_pos.x) + g_cube.curr_map.p_pos.y;
		if (y < 0 || y >= g_cube.curr_map.map_height)
			return (unknown);
		else if (g_cube.curr_map.map[(int)y][(int)x - 1] == 1)
			break ;
		x--;
	}
	res->x = x;
	res->y = y;
	return (east);
}

static t_card	throw_ray_x_right(t_vect *res, t_vect ray, t_card oldcard)
{
	float	m;
	float	x;
	float	y;

	if (ray.x <= 0.f || ray.y == 0.f)
		return (oldcard);
	m = ray.y / ray.x;
	x = floorf(g_cube.curr_map.p_pos.x);
	x++;
	while (x < g_cube.curr_map.map_width)
	{
		y = m * (x - g_cube.curr_map.p_pos.x) + g_cube.curr_map.p_pos.y;
		if (y < 0 || y >= g_cube.curr_map.map_height)
			return (oldcard);
		if (g_cube.curr_map.map[(int)y][(int)x] == 1)
			break ;
		x++;
	}
	res->x = x;
	res->y = y;
	return (west);
}

static t_card	throw_ray_y_down(t_vect *res, t_vect ray, t_card oldcard)
{
	float		m;
	float		x;
	float		y;

	if (ray.y <= 0.f || ray.x == 0.f)
		return (oldcard);
	m = ray.x / ray.y;
	y = (int)g_cube.curr_map.p_pos.y;
	y++;
	while (y < g_cube.curr_map.map_height)
	{
		x = m * (y - g_cube.curr_map.p_pos.y) + g_cube.curr_map.p_pos.x;
		if (x < 0 || x >= g_cube.curr_map.map_width)
			return (oldcard);
		else if (g_cube.curr_map.map[(int)y][(int)x] == 1)
			break ;
		y++;
	}
	if (res->y == 0.f || y <= res->y)
	{
		res->x = x;
		res->y = y;
		return (south);
	}
	return (oldcard);
}

static t_card	throw_ray_y_up(t_vect *res, t_vect ray, t_card oldcard)
{
	float		m;
	float		x;
	float		y;

	if (ray.y >= 0.f || ray.x == 0.f)
		return (oldcard);
	m = ray.x / ray.y;
	y = (int)g_cube.curr_map.p_pos.y;
	while (y > 0 && y < g_cube.curr_map.map_height)
	{
		x = m * (y - g_cube.curr_map.p_pos.y) + g_cube.curr_map.p_pos.x;
		if (x < 0 || x >= g_cube.curr_map.map_width)
			return (oldcard);
		if (g_cube.curr_map.map[(int)y - 1][(int)x] == 1)
			break ;
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

void	raycast(void)
{
	t_vect	wall_hit;
	t_vect	cam;
	t_vect	ray;
	t_card	card;
	int		i;

	cam.x = -g_cube.curr_map.p_dir.y;
	cam.y = g_cube.curr_map.p_dir.x;
	cam.x = (cam.x * 2) / (3 * RES_W / 2);
	cam.y = (cam.y * 2) / (3 * RES_W / 2);
	i = 0;
	while (i < RES_W)
	{
		wall_hit.x = 0.f;
		wall_hit.y = 0.f;
		ray.x = g_cube.curr_map.p_dir.x + (i - RES_W / 2) * cam.x;
		ray.y = g_cube.curr_map.p_dir.y + (i - RES_W / 2) * cam.y;
		card = throw_ray_x_left(&wall_hit, ray);
		card = throw_ray_x_right(&wall_hit, ray, card);
		card = throw_ray_y_up(&wall_hit, ray, card);
		card = throw_ray_y_down(&wall_hit, ray, card);
		put_coloumn_wall(&ray, wall_hit, card, i);
		i++;
	}
}
