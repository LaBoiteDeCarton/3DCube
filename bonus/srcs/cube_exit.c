#include "cub3D.h"
#include "mlx.h"
#include <stdlib.h>

static void	free_map()
{
	for (int i = 0; i < 10; i++)
	{
		free(g_cube.curr_map.map[i]);
	}
	free(g_cube.curr_map.map);
}

void	cube_exit(int exit_status)
{
	if (g_cube.curr_map.textures.n_wall.img_ptr)
		mlx_destroy_image(g_cube.mlx, g_cube.curr_map.textures.n_wall.img_ptr);
	if (g_cube.curr_map.textures.e_wall.img_ptr)
		mlx_destroy_image(g_cube.mlx, g_cube.curr_map.textures.e_wall.img_ptr);
	if (g_cube.curr_map.textures.s_wall.img_ptr)
		mlx_destroy_image(g_cube.mlx, g_cube.curr_map.textures.s_wall.img_ptr);
	if (g_cube.curr_map.textures.w_wall.img_ptr)
		mlx_destroy_image(g_cube.mlx, g_cube.curr_map.textures.w_wall.img_ptr);
	if (g_cube.img_onscreen.img_ptr)
		mlx_destroy_image(g_cube.mlx, g_cube.img_onscreen.img_ptr);
	if (g_cube.img_onload.img_ptr)
		mlx_destroy_image(g_cube.mlx, g_cube.img_onload.img_ptr);
	if (g_cube.img_ready.img_ptr)
		mlx_destroy_image(g_cube.mlx, g_cube.img_ready.img_ptr);
	if (g_cube.win)
		mlx_destroy_window(g_cube.mlx, g_cube.win);
	free_map();
	system("leaks cub3D | grep leaked");
	exit(exit_status);

}