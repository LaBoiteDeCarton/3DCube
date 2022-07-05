#include "cub3D.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	g_cube_set()
{
	g_cube.key_state = 0;
	g_cube.mlx = mlx_init();
	g_cube.win = mlx_new_window(g_cube.mlx, RES_WIDTH, RES_HEIGHT, "42-Cube3D");
	g_cube.img_onscreen.img_ptr = mlx_new_image(g_cube.mlx, RES_WIDTH, RES_HEIGHT);
	g_cube.img_onload.img_ptr = NULL;
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
	{
		handle_errors("Not enough argument");
		return (2);
	}
	g_cube_set();
	if( !try_parse_file(av[1]))
		cube_exit(3);
	loopInGame();
	mlx_loop(g_cube.mlx);
	system("leaks cub3D | grep leaked");
	return (0);
}