#include "cub3D.h"

static void collision()
{
	float	new_posX;
	float	new_posY;

	if (g_cube.curr_map.map[(int)(g_cube.curr_map.p_pos.y)][(int)(g_cube.curr_map.p_pos.x)])
	{
		if (fabs(g_cube.curr_map.p_pos.y - roundf(g_cube.curr_map.p_pos.y)) < fabs(g_cube.curr_map.p_pos.x - roundf(g_cube.curr_map.p_pos.x)))
		{
			g_cube.curr_map.map[(int)(g_cube.curr_map.p_pos.y)][(int)(g_cube.curr_map.p_pos.x)];
			new_posX = ;
			new_posY = ;
		}
		else

	}
}

void	move_left()
{
	float	new_posX;
	float	new_posY;

	new_posX = g_cube.curr_map.p_pos.x + g_cube.curr_map.p_dir.y * 5 / 70;
	new_posY = g_cube.curr_map.p_pos.y - g_cube.curr_map.p_dir.x * 5 / 70;
	if (! g_cube.curr_map.map[(int)(new_posY - 0.3)][(int)(new_posX - 0.3)]
		&& ! g_cube.curr_map.map[(int)(new_posY - 0.3)][(int)(new_posX + 0.3)]
		&& ! g_cube.curr_map.map[(int)(new_posY + 0.3)][(int)(new_posX - 0.3)]
		&& ! g_cube.curr_map.map[(int)(new_posY + 0.3)][(int)(new_posX + 0.3)])
	{
		g_cube.curr_map.p_pos.x = new_posX;
		g_cube.curr_map.p_pos.y	= new_posY;
	}	
	return ;
}

void	move_right()
{
	float	new_posX;
	float	new_posY;
	new_posX = g_cube.curr_map.p_pos.x - g_cube.curr_map.p_dir.y * 5 / 70;
	new_posY = g_cube.curr_map.p_pos.y + g_cube.curr_map.p_dir.x * 5 / 70;
	if (! g_cube.curr_map.map[(int)(new_posY - 0.3)][(int)(new_posX - 0.3)]
		&& ! g_cube.curr_map.map[(int)(new_posY - 0.3)][(int)(new_posX + 0.3)]
		&& ! g_cube.curr_map.map[(int)(new_posY + 0.3)][(int)(new_posX - 0.3)]
		&& ! g_cube.curr_map.map[(int)(new_posY + 0.3)][(int)(new_posX + 0.3)])
	{
		g_cube.curr_map.p_pos.x = new_posX;
		g_cube.curr_map.p_pos.y	= new_posY;
	}	
}

void	move_backward()
{
	float	new_posX;
	float	new_posY;
	new_posX = g_cube.curr_map.p_pos.x - g_cube.curr_map.p_dir.x * 5 / 70;
	new_posY = g_cube.curr_map.p_pos.y - g_cube.curr_map.p_dir.y * 5 / 70;
	if (! g_cube.curr_map.map[(int)(new_posY - 0.3)][(int)(new_posX - 0.3)]
		&& ! g_cube.curr_map.map[(int)(new_posY - 0.3)][(int)(new_posX + 0.3)]
		&& ! g_cube.curr_map.map[(int)(new_posY + 0.3)][(int)(new_posX - 0.3)]
		&& ! g_cube.curr_map.map[(int)(new_posY + 0.3)][(int)(new_posX + 0.3)])
	{
		g_cube.curr_map.p_pos.x = new_posX;
		g_cube.curr_map.p_pos.y	= new_posY;
	}	
}

void	move_forward()
{
	float	new_posX;
	float	new_posY;
	new_posX = g_cube.curr_map.p_pos.x + g_cube.curr_map.p_dir.x * 5 / 70;
	new_posY = g_cube.curr_map.p_pos.y + g_cube.curr_map.p_dir.y * 5 / 70;
	if (! g_cube.curr_map.map[(int)(new_posY - 0.3)][(int)(new_posX - 0.3)]
		&& ! g_cube.curr_map.map[(int)(new_posY - 0.3)][(int)(new_posX + 0.3)]
		&& ! g_cube.curr_map.map[(int)(new_posY + 0.3)][(int)(new_posX - 0.3)]
		&& ! g_cube.curr_map.map[(int)(new_posY + 0.3)][(int)(new_posX + 0.3)])
	{
		g_cube.curr_map.p_pos.x = new_posX;
		g_cube.curr_map.p_pos.y	= new_posY;
	}	
}