#include "cub3D.h"
#include "libft.h"
#include "mlx.h"


#include <stdio.h>
static int add_obj(char **info)
{
	t_parse_data *new_obj;

	if (!info[0] || !info[1])
		return (handle_file_errors("Not enough info about the object"));
	if (ft_strlen(info[1]) != 1)
		return (handle_file_errors("Invalid obj id"));
	new_obj = malloc(sizeof(t_parse_data));
	if (!new_obj)
	{
		handle_errors("unexepcted error when creating object structure");
		return (0);
	}
	new_obj->txtr_path = ft_strdup(info[0]);
	new_obj->c_id = *(info[1]);
	if (info[2])
		new_obj->collectibles = ft_atoi(info[2]);
	else
		new_obj->collectibles = 0;
	new_obj->next = g_cube.p_data;
	g_cube.p_data = new_obj;
	return (1);
}

static int add_vwall(char **info)
{
	t_obj *new_obj;

	if (!info[0] || !info[1])
		return (handle_file_errors("Not enough info about the object"));
	new_obj = malloc(sizeof(t_obj));
	if (!new_obj)
	{
		handle_errors("unexepcted error when creating object structure");
		return (0);
	}
	new_obj->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, info[0], \
		&new_obj->txtr.img_width, &new_obj->txtr.img_height);
	if (!new_obj->txtr.img_ptr)
	{
		free(new_obj);
		return (handle_file_errors("Unable to open xpm file"));
	}
	new_obj->txtr.buffer = mlx_get_data_addr(new_obj->txtr.img_ptr, \
		&new_obj->txtr.bpp, &new_obj->txtr.sl, &new_obj->txtr.endian);
	//if (info[2])
	// ici futur moi va coder les infos supplementaire, si obj est traversable etc
	new_obj->type = v_wall;
	new_obj->pos.x = (float)ft_atoi(info[1]) + 0.5;
	new_obj->pos.y = (float)ft_atoi(info[2]) + 0.5;
	new_obj->start_pos.x = new_obj->pos.x;
	new_obj->start_pos.y = new_obj->pos.y;
	new_obj->size = 1;
	if (!g_cube.curr_map.obj)
		new_obj->id = 0;
	else
		new_obj->id = g_cube.curr_map.obj->id + 1;
	new_obj->next = g_cube.curr_map.obj;
	g_cube.curr_map.obj = new_obj;
	return (1);
}

static int add_hwall(char **info)
{
	t_obj *new_obj;

	if (!info[0] || !info[1])
		return (handle_file_errors("Not enough info about the object"));
	new_obj = malloc(sizeof(t_obj));
	if (!new_obj)
	{
		handle_errors("unexepcted error when creating object structure");
		return (0);
	}
	new_obj->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, info[0], \
		&new_obj->txtr.img_width, &new_obj->txtr.img_height);
	if (!new_obj->txtr.img_ptr)
	{
		free(new_obj);
		return (handle_file_errors("Unable to open xpm file"));
	}
	new_obj->txtr.buffer = mlx_get_data_addr(new_obj->txtr.img_ptr, \
		&new_obj->txtr.bpp, &new_obj->txtr.sl, &new_obj->txtr.endian);
	//if (info[2])
	// ici futur moi va coder les infos supplementaire, si obj est traversable etc
	new_obj->type = h_wall;
	new_obj->pos.x = ft_atoi(info[1]) + 0.5;
	new_obj->pos.y = ft_atoi(info[2]) + 0.5;
	new_obj->start_pos.x = new_obj->pos.x;
	new_obj->start_pos.y = new_obj->pos.y;
	new_obj->size = 1;
	if (!g_cube.curr_map.obj)
		new_obj->id = 0;
	else
		new_obj->id = g_cube.curr_map.obj->id + 1;
	new_obj->next = g_cube.curr_map.obj;
	g_cube.curr_map.obj = new_obj;
	return (1);
}

static int	add_door(char **info)
{
	g_cube.curr_map.door = ft_strdup(*info);
	// g_cube.curr_map.door.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, info[0], \
	// 	&g_cube.curr_map.door.img_width, &g_cube.curr_map.door.img_height);
	// if (!g_cube.curr_map.door.img_ptr)
	// 	return (handle_file_errors("Unable to open xpm file"));
	// g_cube.curr_map.door.buffer = mlx_get_data_addr(g_cube.curr_map.door.img_ptr, \
	// 	&g_cube.curr_map.door.bpp, &g_cube.curr_map.door.sl, &g_cube.curr_map.door.endian);
	return (1);
}

static int	add_color(int *color, char **info)
{
	char	**spl_col;
	int		r;
	int		g;
	int		b;

	if (!info[0] || info[1])
		return (handle_file_errors("Invalud number of argument for element"));
	spl_col = ft_split(*info, ',');
	if (!spl_col[0] || !spl_col[1] || !spl_col[2] || spl_col[3]
		|| !ft_strisdigit(spl_col[0]) || !ft_strisdigit(spl_col[1])
		|| !ft_strisdigit(spl_col[2]))
	{
		free_tab(spl_col);
		return (handle_file_errors("Invalid color element declaration"));
	}
	r = ft_atoi(spl_col[0]);
	g = ft_atoi(spl_col[1]);
	b = ft_atoi(spl_col[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_tab(spl_col);
		return (handle_file_errors("Invalid color range value"));
	}
	*color = r << 16 | g << 8 | b;
	free_tab(spl_col);
	return (1);
}

static int	add_block_texture(char **info)
{
	t_walls *new_wall;

	if (!info[0] || !info[1])
		return (handle_file_errors("Not enough info about the wall"));
	if (!ft_strisdigit(info[1]) && ft_strlen(info[1]) != 1)
		return (handle_file_errors("Invalid wall id"));
	new_wall = malloc(sizeof(t_walls));
	if (!new_wall)
	{
		handle_errors("unexepcted error when creating wall structure");
		return (0);
	}
	new_wall->txtr.img_ptr = mlx_xpm_file_to_image(g_cube.mlx, info[0], \
		&new_wall->txtr.img_width, &new_wall->txtr.img_height);
	if (!new_wall->txtr.img_ptr)
	{
		free(new_wall);
		return (handle_file_errors("Unable to open xpm file"));
	}
	new_wall->txtr.buffer = mlx_get_data_addr(new_wall->txtr.img_ptr, \
		&new_wall->txtr.bpp, &new_wall->txtr.sl, &new_wall->txtr.endian);
	new_wall->id = atoi(info[1]);
	new_wall->next = g_cube.curr_map.w_txtr;
	g_cube.curr_map.w_txtr = new_wall;
	return (1);
}

#include <stdio.h>
static int	add_element(char **info)
{
	printf("info 0 : %s\n", info[0]);
	if (!ft_strncmp(info[0], "BLOCK", 6))
		return (add_block_texture(info + 1));
	else if (!ft_strncmp(info[0], "OBJ", 4))
		return (add_obj(info + 1));
	else if (!ft_strncmp(info[0], "VWALL", 6))
		return (add_vwall(info + 1));
	else if (!ft_strncmp(info[0], "HWALL", 6))
		return (add_hwall(info + 1));
	else if (!ft_strncmp(info[0], "DOOR", 5))
		return (add_door(info + 1));
	else if (!ft_strncmp(info[0], "F", 2))
		return (add_color(&g_cube.curr_map.floor_color, info + 1));
	else if (!ft_strncmp(info[0], "C", 2))
		return (add_color(&g_cube.curr_map.cell_color, info + 1));
	else
		return (handle_file_errors("Invalid element keyname"));
}

static int	is_map(char *line)
{
	while (*line == ' ')
		line++;
	if (*line == '0' || *line == '1' || *line == '3')
		return (1);
	return (0);
}

int	try_parse_element(int fd, char **line)
{
	char	**splitted_line;

	while (get_next_line(fd, line) && !is_map(*line))
	{
		splitted_line = ft_split(*line, ' ');
		free(*line);
		if (splitted_line && splitted_line[0]
			&& !add_element(splitted_line))
		{
			free_tab(splitted_line);
			close(fd);
			return (0);
		}
		free_tab(splitted_line);
	}
	return (1);
}
