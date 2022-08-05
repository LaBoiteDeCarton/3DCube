#include "cub3D.h"
#include <math.h>


#include <stdio.h>
void static	collision_top(float *y, float *posX, float *posY)
{
	t_obj	*obj_ptr;

	if ((g_cube.curr_map.map[(int)(*posY + *y - 0.4)][(int)(*posX - 0.4)] < 31
		&& g_cube.curr_map.map[(int)(*posY + *y - 0.4)][(int)(*posX - 0.4)])
		|| (g_cube.curr_map.map[(int)(*posY + *y - 0.4)][(int)(*posX + 0.4)] < 31
		&& g_cube.curr_map.map[(int)(*posY + *y - 0.4)][(int)(*posX + 0.4)]))
		*y = 0.;
	obj_ptr = g_cube.curr_map.obj;
	while (obj_ptr)
	{
		if (*posY - 0.4 > obj_ptr->pos.y && *posY - 0.4 + *y < obj_ptr->pos.y
			&& ((*posX - 0.4 > obj_ptr->pos.x - 0.5 && *posX - 0.4 < obj_ptr->pos.x + 0.5)
			|| (*posX + 0.4 > obj_ptr->pos.x - 0.5 && *posX + 0.4 < obj_ptr->pos.x + 0.5)))
		{
			if (!obj_ptr->collectibles)
			{
				*y = 0.;
				break ;
			}
			else
				collect_object(obj_ptr);
		}
		obj_ptr = obj_ptr->next;
	}
}

void static	collision_bottom(float *y, float *posX, float *posY)
{
	t_obj	*obj_ptr;

	if ((g_cube.curr_map.map[(int)(*posY + *y + 0.4)][(int)(*posX - 0.4)] < 31
		&& g_cube.curr_map.map[(int)(*posY + *y + 0.4)][(int)(*posX - 0.4)])
		|| (g_cube.curr_map.map[(int)(*posY + *y + 0.4)][(int)(*posX + 0.4)] < 31
		&& g_cube.curr_map.map[(int)(*posY + *y + 0.4)][(int)(*posX + 0.4)]))
		*y = 0.;
	obj_ptr = g_cube.curr_map.obj;
	while (obj_ptr)
	{
		if (*posY + 0.4 < obj_ptr->pos.y && *posY + 0.4 + *y > obj_ptr->pos.y
			&& ((*posX - 0.4 > obj_ptr->pos.x - 0.5 && *posX - 0.4 < obj_ptr->pos.x + 0.5)
			|| (*posX + 0.4 > obj_ptr->pos.x - 0.5 && *posX + 0.4 < obj_ptr->pos.x + 0.5)))
		{
			if (!obj_ptr->collectibles)
			{
				*y = 0.;
				break ;
			}
			else
				collect_object(obj_ptr);
		}
		obj_ptr = obj_ptr->next;
	}
}

void static	collision_left(float *x, float *posX, float *posY)
{
	t_obj	*obj_ptr;

	if ((g_cube.curr_map.map[(int)(*posY + 0.4)][(int)(*posX + *x - 0.4)] < 31
		&& g_cube.curr_map.map[(int)(*posY + 0.4)][(int)(*posX + *x - 0.4)])
		|| (g_cube.curr_map.map[(int)(*posY - 0.4)][(int)(*posX + *x - 0.4)] < 31
		&& g_cube.curr_map.map[(int)(*posY - 0.4)][(int)(*posX + *x - 0.4)]))
		*x = 0.;
	obj_ptr = g_cube.curr_map.obj;
	while (obj_ptr)
	{
		if (*posX - 0.4 > obj_ptr->pos.x && *posX - 0.4 + *x < obj_ptr->pos.x
			&& ((*posY - 0.4 > obj_ptr->pos.y - 0.5 && *posY - 0.4 < obj_ptr->pos.y + 0.5)
			|| (*posY + 0.4 > obj_ptr->pos.y - 0.5 && *posY + 0.4 < obj_ptr->pos.y + 0.5)))
		{
			if (!obj_ptr->collectibles)
			{
				*x = 0.;
				break ;
			}
			else
				collect_object(obj_ptr);
		}
		obj_ptr = obj_ptr->next;
	}
}

void static	collision_right(float *x, float *posX, float *posY)
{
	t_obj	*obj_ptr;

	if ((g_cube.curr_map.map[(int)(*posY + 0.4)][(int)(*posX + *x + 0.4)] < 31
		&& g_cube.curr_map.map[(int)(*posY + 0.4)][(int)(*posX + *x + 0.4)])
		|| (g_cube.curr_map.map[(int)(*posY - 0.4)][(int)(*posX + *x + 0.4)] < 31
		&& g_cube.curr_map.map[(int)(*posY - 0.4)][(int)(*posX + *x + 0.4)]))
		*x = 0.;
	obj_ptr = g_cube.curr_map.obj;
	while (obj_ptr)
	{
		if (*posX + 0.4 < obj_ptr->pos.x && *posX + 0.4 + *x > obj_ptr->pos.x
			&& ((*posY - 0.4 > obj_ptr->pos.y - 0.5 && *posY - 0.4 < obj_ptr->pos.y + 0.5)
			|| (*posY + 0.4 > obj_ptr->pos.y - 0.5 && *posY + 0.4 < obj_ptr->pos.y + 0.5)))
		{
			if (!obj_ptr->collectibles)
			{
				*x = 0.;
				break ;
			}
			else
				collect_object(obj_ptr);
		}
		obj_ptr = obj_ptr->next;
	}
}

void collision_solver(float *add_to_x, float *add_to_y)
{
	float	*posX;
	float	*posY;

	posX = &(g_cube.curr_map.p_pos.x);
	posY = &(g_cube.curr_map.p_pos.y);
	if (fabsf(*add_to_x) <= fabsf(*add_to_y))
	{
		if (*add_to_y <= 0)
			collision_top(add_to_y, posX, posY);
		else if (*add_to_y > 0)
			collision_bottom(add_to_y, posX, posY);
		if (*add_to_x <= 0)
			collision_left(add_to_x, posX, posY);
		else if (*add_to_x > 0)
			collision_right(add_to_x, posX, posY);
	}
	if (fabsf(*add_to_x) > fabsf(*add_to_y))
	{
		if (*add_to_x <= 0)
			collision_left(add_to_x, posX, posY);
		else if (*add_to_x > 0)
			collision_right(add_to_x, posX, posY);
		if (*add_to_y <= 0)
			collision_top(add_to_y, posX, posY);
		else if (*add_to_y > 0)
			collision_bottom(add_to_y, posX, posY);
	}
}