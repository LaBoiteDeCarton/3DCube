#include "cub3D.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	g_cube_set(void)
{
	g_cube.key_state = 0;
	g_cube.mlx = mlx_init();
	g_cube.win = mlx_new_window(g_cube.mlx, RES_W, RES_H, "42-Cube3D");
	g_cube.rcimg.img_ptr = NULL;
	g_cube.curr_map.map = NULL;
	g_cube.curr_map.p_dir.x = 0.;
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
	if (!try_parse_file(av[1]))
		cube_exit(EXIT_FAILURE);
	loopInGame();
	mlx_loop(g_cube.mlx);
	system("leaks cub3D | grep leaked");
	return (0);
}
