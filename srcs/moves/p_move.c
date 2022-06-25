#include "cub3D.h"

void	move_left()
{
	g_cube.curr_map.p_pos.x -= g_cube.curr_map.p_dir.y;
	g_cube.curr_map.p_pos.y -= g_cube.curr_map.p_dir.x;
}

void	move_right()
{
	g_cube.curr_map.p_pos.x += g_cube.curr_map.p_dir.y;
	g_cube.curr_map.p_pos.y += g_cube.curr_map.p_dir.x;
}

void	move_backward()
{
	g_cube.curr_map.p_pos.x += g_cube.curr_map.p_dir.x;
	g_cube.curr_map.p_pos.y += g_cube.curr_map.p_dir.y;
}

void	move_forward()
{
	g_cube.curr_map.p_pos.x -= g_cube.curr_map.p_dir.x;
	g_cube.curr_map.p_pos.y -= g_cube.curr_map.p_dir.y;
}