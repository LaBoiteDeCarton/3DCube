#include "cub3D.h"
#include <math.h>
#include <stdio.h>

void	rotate_left(void)
{
	float	cosa;
	float	sina;
	float	new_dirX;
	float	new_dirY;

	cosa = cos(-0.05);
	sina = sin(-0.05);
	new_dirX = g_cube.curr_map.p_dir.x * cosa - g_cube.curr_map.p_dir.y * sina;
	new_dirY = g_cube.curr_map.p_dir.x * sina + g_cube.curr_map.p_dir.y * cosa;
	g_cube.curr_map.p_dir.x = new_dirX;
	g_cube.curr_map.p_dir.y = new_dirY;
}

void	rotate_right(void)
{
	float	cosa;
	float	sina;
	float	new_dirX;
	float	new_dirY;

	cosa = cos(0.05);
	sina = sin(0.05);
	new_dirX = g_cube.curr_map.p_dir.x * cosa - g_cube.curr_map.p_dir.y * sina;
	new_dirY = g_cube.curr_map.p_dir.x * sina + g_cube.curr_map.p_dir.y * cosa;
	g_cube.curr_map.p_dir.x = new_dirX;
	g_cube.curr_map.p_dir.y = new_dirY;
}

void	rotate(float	angle)
{
	float	cosa;
	float	sina;
	float	new_dirX;
	float	new_dirY;

	cosa = cos(angle);
	sina = sin(angle);
	new_dirX = g_cube.curr_map.p_dir.x * cosa - g_cube.curr_map.p_dir.y * sina;
	new_dirY = g_cube.curr_map.p_dir.x * sina + g_cube.curr_map.p_dir.y * cosa;
	g_cube.curr_map.p_dir.x = new_dirX;
	g_cube.curr_map.p_dir.y = new_dirY;
}
