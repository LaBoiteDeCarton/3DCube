#include "cub3D.h"
#include <fcntl.h>
#include <stdlib.h>
#include "mlx.h"
#include <stdio.h>

static int	key_press_hook(int keycode)
{

	printf("Key pressed : %d\n", keycode);
	if( keycode == K_A_UP)
		return (0);
	else if( keycode == K_A_DOWN)
		return (0);
	else if (keycode == 53)
		cube_exit();
	return (0);
}

static int key_release_hook(int keycode)
{
	(void)keycode;
	return (0);
}

void	display_menu()
{
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu_bg.ptr, 0, 0);
}

static int	loop_hook()
{
	display_menu();
	mlx_string_put(g_cube.mlx, g_cube.win, RES_WIDTH/2, RES_HEIGHT/2, 0xfffafa, "Play");
	return (0);
}

void	loopMenu()
{
	mlx_hook(g_cube.win, 2, 1L << 0, key_press_hook, NULL);
	mlx_hook(g_cube.win, 3, 1L << 1, key_release_hook, NULL);
	mlx_loop_hook(g_cube.mlx, loop_hook, NULL);
}