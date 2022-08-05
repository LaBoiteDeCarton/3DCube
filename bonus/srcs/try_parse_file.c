// #include "cub3D.h"
// #include "mlx.h"
// #include "libft.h"
// #include <fcntl.h>

// #include <stdio.h>
// #include <math.h>
// #define _USE_MATH_DEFINES

// int		try_parse_file(char *pathfile)
// {
// 	int		fd;
// 	//char	*line;
// 	int		valid_file;

// 	valid_file = 0;
// 	if (ft_strncmp(ft_strrchr(pathfile, '.'), ".cub", 5))
// 		return (0);
// 	fd = open(pathfile, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		handle_errors(pathfile);
// 		return (0);
// 	}
// 	// while (get_next_line(fd, &line))
// 	// {

// 	// }

// 	//Ici je fait une map a la maison, le parsing est a faire.
// 	g_cube.curr_map.map = malloc(sizeof(short int *) * 10);
// 	for (int i = 0; i < 10; i++)
// 	{
// 		g_cube.curr_map.map[i] = malloc(sizeof(short int) * 10);
// 		if (i == 0 || i == 9)
// 		{
// 			for (int j = 0; j < 10; j++)
// 				g_cube.curr_map.map[i][j] = 1;
// 		}
// 		else
// 		{
// 			for (int j = 0; j < 10; j++)
// 				g_cube.curr_map.map[i][j] = 0;
// 			g_cube.curr_map.map[i][0] = 2;
// 			g_cube.curr_map.map[i][9] = 1;
// 		}
// 	}

// 	g_cube.curr_map.map[1][3] = 1;
// 	g_cube.curr_map.map[1][7] = 3;
// 	g_cube.curr_map.map[2][3] = 1;
// 	g_cube.curr_map.map[2][7] = 3;
// 	g_cube.curr_map.map[2][5] = 1;
// 	g_cube.curr_map.map[5][0] = 1;
// 	g_cube.curr_map.map_width = 10;
// 	g_cube.curr_map.map_height = 10;
// 	g_cube.curr_map.p_pos.x = 5;
// 	g_cube.curr_map.p_pos.y = 8;
// 	g_cube.curr_map.p_dir.x = cos(3 * M_PI / 2 + 0.0001);
// 	g_cube.curr_map.p_dir.y = sin(3 * M_PI / 2 + 0.0001);

// 	t_walls *wall_ptr;
// 	//Le parsing doit aussi pouvir extraire les textures a utiliser
// 	g_cube.curr_map.w_txtr = malloc(sizeof(t_walls));
// 	wall_ptr = g_cube.curr_map.w_txtr;
// 	wall_ptr->id = 1;
// 	wall_ptr->next = NULL;
// 	wall_ptr->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/TECH_2A.xpm", &wall_ptr->txtr.img_width, &wall_ptr->txtr.img_height);
// 	wall_ptr->txtr.buffer = mlx_get_data_addr(wall_ptr->txtr.img_ptr, &wall_ptr->txtr.bpp, &wall_ptr->txtr.sl, &wall_ptr->txtr.endian);



// 	wall_ptr->next = malloc(sizeof(t_walls));
// 	wall_ptr = wall_ptr->next;
// 	wall_ptr->id = 2;
// 	wall_ptr->next = NULL;
// 	wall_ptr->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/DOOR_WIND.xpm", &wall_ptr->txtr.img_width, &wall_ptr->txtr.img_height);
// 	wall_ptr->txtr.buffer = mlx_get_data_addr(wall_ptr->txtr.img_ptr, &wall_ptr->txtr.bpp, &wall_ptr->txtr.sl, &wall_ptr->txtr.endian);
	


// 	wall_ptr->next = malloc(sizeof(t_walls));
// 	wall_ptr = wall_ptr->next;
// 	wall_ptr->id = 3;
// 	wall_ptr->next = NULL;
// 	wall_ptr->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/TECH_3E.xpm", &wall_ptr->txtr.img_width, &wall_ptr->txtr.img_height);
// 	wall_ptr->txtr.buffer = mlx_get_data_addr(wall_ptr->txtr.img_ptr, &wall_ptr->txtr.bpp, &wall_ptr->txtr.sl, &wall_ptr->txtr.endian);


// 	// g_cube.curr_map.obj = NULL;
// 	t_obj	*obj;
// 	g_cube.curr_map.obj = malloc(sizeof(t_obj));
// 	obj = g_cube.curr_map.obj;
// 	obj->next = NULL;
// 	obj->type = h_door;
// 	obj->id = 42;
// 	obj->size = 1;
// 	obj->pos.x = 4.5;
// 	obj->pos.y = 2.5;
// 	obj->start_pos.x = 4.5;
// 	obj->start_pos.y = 2.5;
// 	obj->bool_move = 0;
// 	obj->move_dir.x = -1;
// 	obj->move_dir.y = 0;
// 	obj->txtr.img_ptr = NULL;
// 	obj->txtr.buffer = NULL;
// 	obj->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/LIGHT_1B.xpm", &obj->txtr.img_width, &obj->txtr.img_height);
// 	obj->txtr.buffer = mlx_get_data_addr(obj->txtr.img_ptr, &obj->txtr.bpp, &obj->txtr.sl, &obj->txtr.endian);
	
// 	obj->next = malloc(sizeof(t_obj));
// 	obj = obj->next;
// 	obj->next = NULL;
// 	obj->type = h_door;
// 	obj->id = 43;
// 	obj->size = 1;
// 	obj->pos.x = 6.5;
// 	obj->pos.y = 2.5;
// 	obj->start_pos.x = 6.5;
// 	obj->start_pos.y = 2.5;
// 	obj->bool_move = 0;
// 	obj->move_dir.x = -1;
// 	obj->move_dir.y = 0;
// 	obj->txtr.img_ptr = NULL;
// 	obj->txtr.buffer = NULL;
// 	obj->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/DOOR_WIND.xpm", &obj->txtr.img_width, &obj->txtr.img_height);
// 	obj->txtr.buffer = mlx_get_data_addr(obj->txtr.img_ptr, &obj->txtr.bpp, &obj->txtr.sl, &obj->txtr.endian);

// 	obj->next = malloc(sizeof(t_obj));
// 	obj = obj->next;
// 	obj->next = NULL;
// 	obj->type = sprite;
// 	obj->id = 44;
// 	obj->size = 1;
// 	obj->pos.x = 2;
// 	obj->pos.y = 2;
// 	obj->start_pos.x = 2;
// 	obj->start_pos.y = 2;
// 	obj->bool_move = 0;
// 	obj->move_dir.x = 0;
// 	obj->move_dir.y = 0;
// 	obj->txtr.img_ptr = NULL;
// 	obj->txtr.buffer = NULL;
// 	obj->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/greenlight.xpm", &obj->txtr.img_width, &obj->txtr.img_height);
// 	obj->txtr.buffer = mlx_get_data_addr(obj->txtr.img_ptr, &obj->txtr.bpp, &obj->txtr.sl, &obj->txtr.endian);

// 	obj->next = malloc(sizeof(t_obj));
// 	obj = obj->next;
// 	obj->next = NULL;
// 	obj->type = sprite;
// 	obj->id = 45;
// 	obj->size = 1;
// 	obj->pos.x = 8.5;
// 	obj->pos.y = 3.5;
// 	obj->start_pos.x = 8.5;
// 	obj->start_pos.y = 3.5;
// 	obj->bool_move = 0;
// 	obj->move_dir.x = 0;
// 	obj->move_dir.y = 0;
// 	obj->txtr.img_ptr = NULL;
// 	obj->txtr.buffer = NULL;
// 	obj->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/pillar.xpm", &obj->txtr.img_width, &obj->txtr.img_height);
// 	obj->txtr.buffer = mlx_get_data_addr(obj->txtr.img_ptr, &obj->txtr.bpp, &obj->txtr.sl, &obj->txtr.endian);
// 	// wall_ptr->next = malloc(sizeof(t_walls));
// 	// wall_ptr = wall_ptr->next;
// 	// wall_ptr->id = 255;
// 	// wall_ptr->next = NULL;
// 	// wall_ptr->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/mossy.xpm", &wall_ptr->txtr.img_width, &wall_ptr->txtr.img_height);
// 	// wall_ptr->txtr.buffer = mlx_get_data_addr(wall_ptr->txtr.img_ptr, &wall_ptr->txtr.bpp, &wall_ptr->txtr.sl, &wall_ptr->txtr.endian);

// 	// wall_ptr->next = malloc(sizeof(t_walls));
// 	// wall_ptr = wall_ptr->next;
// 	// wall_ptr->id = 254;
// 	// wall_ptr->next = NULL;
// 	// wall_ptr->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/mossy.xpm", &wall_ptr->txtr.img_width, &wall_ptr->txtr.img_height);
// 	// wall_ptr->txtr.buffer = mlx_get_data_addr(wall_ptr->txtr.img_ptr, &wall_ptr->txtr.bpp, &wall_ptr->txtr.sl, &wall_ptr->txtr.endian);
// 	//on doit set aussi les couleurs de floor et cell
// 	g_cube.curr_map.floor_color = 0x00aaaaaa;
// 	g_cube.curr_map.cell_color = 0x00303030;

// 	g_cube.curr_map.background.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, "texture/view.xpm", &g_cube.curr_map.background.img_width, &g_cube.curr_map.background.img_height);
// 	g_cube.curr_map.background.buffer = mlx_get_data_addr(g_cube.curr_map.background.img_ptr, &g_cube.curr_map.background.bpp, &g_cube.curr_map.background.sl, &g_cube.curr_map.background.endian);

// 	//On renvoi 1 si aucune erreur est rencontré. Dans le cas contraire handle error est utilisé et un code retour 0 est envoyé par la fonction
// 	return (1);
// }