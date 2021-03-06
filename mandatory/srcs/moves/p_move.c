#include "cub3D.h"

void	move_left()
{
	float	add_to_x;
	float	add_to_y;

	add_to_x = g_cube.curr_map.p_dir.y * 5 / 70;
	add_to_y = - g_cube.curr_map.p_dir.x * 5 / 70;

	collision_solver(&add_to_x, &add_to_y);
	g_cube.curr_map.p_pos.x += add_to_x;
	g_cube.curr_map.p_pos.y += add_to_y;
	return ;
}

void	move_right()
{
	float	add_to_x;
	float	add_to_y;

	add_to_x = - g_cube.curr_map.p_dir.y * 5 / 70;
	add_to_y = g_cube.curr_map.p_dir.x * 5 / 70;

	collision_solver(&add_to_x, &add_to_y);
	g_cube.curr_map.p_pos.x += add_to_x;
	g_cube.curr_map.p_pos.y += add_to_y;
}

void	move_backward()
{
	float	add_to_x;
	float	add_to_y;

	add_to_x = - g_cube.curr_map.p_dir.x * 5 / 70;
	add_to_y = - g_cube.curr_map.p_dir.y * 5 / 70;

	collision_solver(&add_to_x, &add_to_y);
	g_cube.curr_map.p_pos.x += add_to_x;
	g_cube.curr_map.p_pos.y += add_to_y;
}

void	move_forward()
{
	float	add_to_x;
	float	add_to_y;

	add_to_x = g_cube.curr_map.p_dir.x * 5 / 70;
	add_to_y = g_cube.curr_map.p_dir.y * 5 / 70;

	collision_solver(&add_to_x, &add_to_y);
	g_cube.curr_map.p_pos.x += add_to_x;
	g_cube.curr_map.p_pos.y += add_to_y;
}