#include "cub3D.h"
#include <math.h>

void static	collision_top(float *y, float posX, float posY)
{
	if (g_cube.curr_map.map[(int)(posY + *y - 0.4)][(int)(posX - 0.4)]
		|| g_cube.curr_map.map[(int)(posY + *y - 0.4)][(int)(posX + 0.4)])
		*y = 0.;
}

void static	collision_bottom(float *y, float posX, float posY)
{
	if (g_cube.curr_map.map[(int)(posY + *y + 0.4)][(int)(posX - 0.4)]
		|| g_cube.curr_map.map[(int)(posY + *y + 0.4)][(int)(posX + 0.4)])
		*y = 0.;
}

void static	collision_left(float *x, float posX, float posY)
{
	if (g_cube.curr_map.map[(int)(posY + 0.4)][(int)(posX + *x - 0.4)]
		|| g_cube.curr_map.map[(int)(posY - 0.4)][(int)(posX + *x - 0.4)])
		*x = 0.;
}

void static	collision_right(float *x, float posX, float posY)
{
	if (g_cube.curr_map.map[(int)(posY + 0.4)][(int)(posX + *x + 0.4)]
		|| g_cube.curr_map.map[(int)(posY - 0.4)][(int)(posX + *x + 0.4)])
		*x = 0.;
}

void	collision_solver(float *add_to_x, float *add_to_y)
{
	t_vect	pos;

	pos = g_cube.curr_map.p_pos;
	if (fabsf(*add_to_x) <= fabsf(*add_to_y))
	{
		if (*add_to_y <= 0)
			collision_top(add_to_y, pos.x, pos.y);
		else
			collision_bottom(add_to_y, pos.x, pos.y);
		if (*add_to_x <= 0)
			collision_left(add_to_x, pos.x, pos.y);
		else
			collision_right(add_to_x, pos.x, pos.y);
	}
	if (fabsf(*add_to_x) > fabsf(*add_to_y))
	{
		if (*add_to_x <= 0)
			collision_left(add_to_x, pos.x, pos.y);
		else
			collision_right(add_to_x, pos.x, pos.y);
		if (*add_to_y <= 0)
			collision_top(add_to_y, pos.x, pos.y);
		else
			collision_bottom(add_to_y, pos.x, pos.y);
	}
}
