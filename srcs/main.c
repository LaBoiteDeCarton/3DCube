#include "cub3D.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
 #include <fcntl.h>


int		try_create_map_from_file(char *pathfile)
{
	int		fd;
	//char	*line;
	int		valid_file;

	valid_file = 0;
	if (ft_strncmp(ft_strrchr(pathfile, '.'), ".cub", 5))
		return (0);
	fd = open(pathfile, O_RDONLY);
	if (fd == -1)
	{
		handle_errors(pathfile);
		return (0);
	}
	// while (get_next_line(fd, &line))
	// {

	// }
	g_cube.curr_map.map = malloc(sizeof(short int *) * 10);
	for (int i = 0; i < 10; i++)
	{
		g_cube.curr_map.map[i] = malloc(sizeof(short int) * 10);
		if (i == 0 || i == 9)
		{
			for (int j = 0; j < 10; j++)
				g_cube.curr_map.map[i][j] = 1;
		}
		else
		{
			for (int j = 0; j < 10; j++)
				g_cube.curr_map.map[i][j] = 0;
			g_cube.curr_map.map[i][0] = 1;
			g_cube.curr_map.map[i][9] = 1;
		}
	}
	g_cube.curr_map.p_pos.x = 5;
	g_cube.curr_map.p_pos.y = 4;
	g_cube.curr_map.p_dir.x = 0.0;
	g_cube.curr_map.p_dir.y = 0.01;
	return (1);
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
	{
		handle_errors("Not enough argument");
		return (2);
	}
	if( !try_create_map_from_file(av[1]))
	{
		return (3);
	}
	g_cube.key_state = 0;
	g_cube.mlx = mlx_init();
	g_cube.win = mlx_new_window(g_cube.mlx, RES_WIDTH, RES_HEIGHT, "42-Cube3D");
	g_cube.img = mlx_new_image(g_cube.mlx, RES_WIDTH, RES_HEIGHT);
	g_cube.menu_bg.ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/menu_bg.xpm", &g_cube.menu_bg.img_width, &g_cube.menu_bg.img_height);
	loopMenu();
	mlx_loop(g_cube.mlx);
	system("leaks cub3D | grep leaked");
	return (0);
}