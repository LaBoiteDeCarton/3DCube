#include "cub3D.h"
#include <math.h>
#include <stdio.h>

void	rotate_left()
{
	float cosa = cos(-0.05);
	float sina = sin(-0.05);
	float new_dirX;
	float new_dirY;

	new_dirX = g_cube.curr_map.p_dir.x * cosa - g_cube.curr_map.p_dir.y * sina;
	new_dirY = g_cube.curr_map.p_dir.x * sina + g_cube.curr_map.p_dir.y * cosa;
	g_cube.curr_map.p_dir.x = new_dirX;
	g_cube.curr_map.p_dir.y = new_dirY;
}

void	rotate_right()
{
	float cosa = cos(0.05);
	float sina = sin(0.05);
	float new_dirX;
	float new_dirY;

	new_dirX = g_cube.curr_map.p_dir.x * cosa - g_cube.curr_map.p_dir.y * sina;
	new_dirY = g_cube.curr_map.p_dir.x * sina + g_cube.curr_map.p_dir.y * cosa;
	g_cube.curr_map.p_dir.x = new_dirX;
	g_cube.curr_map.p_dir.y = new_dirY;
}

void	rotate(float angle)
{
	float cosa = cos(angle);
	float sina = sin(angle);
	float new_dirX;
	float new_dirY;

	new_dirX = g_cube.curr_map.p_dir.x * cosa - g_cube.curr_map.p_dir.y * sina;
	new_dirY = g_cube.curr_map.p_dir.x * sina + g_cube.curr_map.p_dir.y * cosa;
	g_cube.curr_map.p_dir.x = new_dirX;
	g_cube.curr_map.p_dir.y = new_dirY;
}