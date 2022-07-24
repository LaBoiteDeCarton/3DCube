#include "cub3D.h"
#include "mlx.h"
#include "libft.h"
#include <fcntl.h>

int		try_parse_file(char *pathfile)
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

	//Ici je fait une map a la maison, le parsing est a faire.
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
			g_cube.curr_map.map[i][0] = 2;
			g_cube.curr_map.map[i][9] = 1;
		}
	}

	g_cube.curr_map.map[1][3] = 1;
	g_cube.curr_map.map[1][7] = 2;
	g_cube.curr_map.map[2][3] = 1;
	g_cube.curr_map.map[2][7] = 3;
	g_cube.curr_map.map[2][5] = 1;
	g_cube.curr_map.map[2][4] = 3;
	g_cube.curr_map.map_width = 10;
	g_cube.curr_map.map_height = 10;
	g_cube.curr_map.p_pos.x = 5;
	g_cube.curr_map.p_pos.y = 8;
	g_cube.curr_map.p_dir.x = 0.0;
	g_cube.curr_map.p_dir.y = -1.;

	t_walls *wall_ptr;
	//Le parsing doit aussi pouvir extraire les textures a utiliser
	g_cube.curr_map.w_txtr = malloc(sizeof(t_walls));
	wall_ptr = g_cube.curr_map.w_txtr;
	wall_ptr->id = 1;
	wall_ptr->next = NULL;
	wall_ptr->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/TECH_2A.xpm", &wall_ptr->txtr.img_width, &wall_ptr->txtr.img_height);
	wall_ptr->txtr.buffer = mlx_get_data_addr(wall_ptr->txtr.img_ptr, &wall_ptr->txtr.bpp, &wall_ptr->txtr.sl, &wall_ptr->txtr.endian);

	wall_ptr->next = malloc(sizeof(t_walls));
	wall_ptr = wall_ptr->next;
	wall_ptr->id = 2;
	wall_ptr->next = NULL;
	wall_ptr->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/TECH_3E.xpm", &wall_ptr->txtr.img_width, &wall_ptr->txtr.img_height);
	wall_ptr->txtr.buffer = mlx_get_data_addr(wall_ptr->txtr.img_ptr, &wall_ptr->txtr.bpp, &wall_ptr->txtr.sl, &wall_ptr->txtr.endian);
	
	wall_ptr->next = malloc(sizeof(t_walls));
	wall_ptr = wall_ptr->next;
	wall_ptr->id = 3;
	wall_ptr->next = NULL;
	wall_ptr->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/CRATE_1E.xpm", &wall_ptr->txtr.img_width, &wall_ptr->txtr.img_height);
	wall_ptr->txtr.buffer = mlx_get_data_addr(wall_ptr->txtr.img_ptr, &wall_ptr->txtr.bpp, &wall_ptr->txtr.sl, &wall_ptr->txtr.endian);
	// wall_ptr->next = malloc(sizeof(t_walls));
	// wall_ptr = wall_ptr->next;
	// wall_ptr->id = 255;
	// wall_ptr->next = NULL;
	// wall_ptr->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/mossy.xpm", &wall_ptr->txtr.img_width, &wall_ptr->txtr.img_height);
	// wall_ptr->txtr.buffer = mlx_get_data_addr(wall_ptr->txtr.img_ptr, &wall_ptr->txtr.bpp, &wall_ptr->txtr.sl, &wall_ptr->txtr.endian);

	// wall_ptr->next = malloc(sizeof(t_walls));
	// wall_ptr = wall_ptr->next;
	// wall_ptr->id = 254;
	// wall_ptr->next = NULL;
	// wall_ptr->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/mossy.xpm", &wall_ptr->txtr.img_width, &wall_ptr->txtr.img_height);
	// wall_ptr->txtr.buffer = mlx_get_data_addr(wall_ptr->txtr.img_ptr, &wall_ptr->txtr.bpp, &wall_ptr->txtr.sl, &wall_ptr->txtr.endian);
	//on doit set aussi les couleurs de floor et cell
	g_cube.curr_map.cell_color = 0x00aaaaaa;
	g_cube.curr_map.floor_color = 0x00303030;

	//On renvoi 1 si aucune erreur est rencontré. Dans le cas contraire handle error est utilisé et un code retour 0 est envoyé par la fonction
	return (1);
}