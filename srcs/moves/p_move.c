#include "cub3D.h"

void	move_left()
{
	g_cube.curr_map.p_pos.x += g_cube.curr_map.p_dir.y * 5 / 70;
	g_cube.curr_map.p_pos.y	-= g_cube.curr_map.p_dir.x * 5 / 70;
}

void	move_right()
{
	g_cube.curr_map.p_pos.x -= g_cube.curr_map.p_dir.y * 5 / 70;
	g_cube.curr_map.p_pos.y += g_cube.curr_map.p_dir.x * 5 / 70;
}

void	move_backward()
{
	g_cube.curr_map.p_pos.x -= g_cube.curr_map.p_dir.x * 5 / 70;
	g_cube.curr_map.p_pos.y -= g_cube.curr_map.p_dir.y * 5 / 70;
}

void	move_forward()
{
	g_cube.curr_map.p_pos.x += g_cube.curr_map.p_dir.x * 5 / 70;
	g_cube.curr_map.p_pos.y += g_cube.curr_map.p_dir.y * 5 / 70;
}