#include "cub3D.h"
#include "mlx.h"
#include <stdlib.h>

void	cube_exit(int exit_status)
{
	if (g_cube.win)
		mlx_destroy_window(g_cube.mlx, g_cube.win);
	free_map();
	system("leaks cub3D | grep leaked");
	exit(exit_status);
}