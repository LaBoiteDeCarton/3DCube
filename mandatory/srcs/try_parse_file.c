#include "cub3D.h"
#include "mlx.h"
#include "libft.h"
#include <fcntl.h>

static int		try_open_file(char *pathfile)
{
	int		fd;

	if (ft_strncmp(ft_strrchr(pathfile, '.'), ".cub", 5))
		return (-1);
	fd = open(pathfile, O_RDONLY);
	if (fd == -1)
	{
		handle_errors(pathfile);
		return (-1);
	}
	return (fd);
}

int		try_parse_file(char *pathfile)
{
	int		fd;
	//char	*line;
	int		valid_file;

	fd = try_open_file(pathfile);
	if (fd == -1)
		return (0);
	

	// while (get_next_line(fd, &line))
	// {

	// }

	//Ici je fait une map a la main, le parsing est a faire.
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

	g_cube.curr_map.map[1][3] = 1;
	g_cube.curr_map.map[1][7] = 1;
	g_cube.curr_map.map[2][3] = 1;
	g_cube.curr_map.map[2][7] = 1;
	g_cube.curr_map.map_width = 10;
	g_cube.curr_map.map_height = 10;
	g_cube.curr_map.p_pos.x = 5;
	g_cube.curr_map.p_pos.y = 8;
	g_cube.curr_map.p_dir.x = 0.0;
	g_cube.curr_map.p_dir.y = -1.;

	//Le parsing doit aussi pouvir extraire les textures a utiliser
	g_cube.curr_map.n_wall.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/bluestone.xpm", &g_cube.curr_map.n_wall.img_width, &g_cube.curr_map.n_wall.img_height);
	g_cube.curr_map.n_wall.buffer = mlx_get_data_addr(g_cube.curr_map.n_wall.img_ptr, &g_cube.curr_map.n_wall.bpp, &g_cube.curr_map.n_wall.sl, &g_cube.curr_map.n_wall.endian);
	g_cube.curr_map.s_wall.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/wood.xpm", &g_cube.curr_map.s_wall.img_width, &g_cube.curr_map.s_wall.img_height);
	g_cube.curr_map.s_wall.buffer = mlx_get_data_addr(g_cube.curr_map.s_wall.img_ptr, &g_cube.curr_map.s_wall.bpp, &g_cube.curr_map.s_wall.sl, &g_cube.curr_map.s_wall.endian);
	g_cube.curr_map.e_wall.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/greystone.xpm", &g_cube.curr_map.e_wall.img_width, &g_cube.curr_map.e_wall.img_height);
	g_cube.curr_map.e_wall.buffer = mlx_get_data_addr(g_cube.curr_map.e_wall.img_ptr, &g_cube.curr_map.e_wall.bpp, &g_cube.curr_map.e_wall.sl, &g_cube.curr_map.e_wall.endian);
	g_cube.curr_map.w_wall.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/mossy.xpm", &g_cube.curr_map.w_wall.img_width, &g_cube.curr_map.w_wall.img_height);
	g_cube.curr_map.w_wall.buffer = mlx_get_data_addr(g_cube.curr_map.w_wall.img_ptr, &g_cube.curr_map.w_wall.bpp, &g_cube.curr_map.w_wall.sl, &g_cube.curr_map.w_wall.endian);
	//on doit set aussi les couleurs de floor et cell
	g_cube.curr_map.cell_color = 0x00501050;
	g_cube.curr_map.floor_color = 0x00304f2f;

	//On renvoi 1 si aucune erreur est rencontré. Dans le cas contraire handle error est utilisé et un code retour 0 est envoyé par la fonction
	return (1);
}