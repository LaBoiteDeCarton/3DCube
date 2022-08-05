#include "cub3D.h"
#include "libft.h"
#include <stdlib.h>
#include <math.h>
#define	_USE_MATH_DEFINES

static int	add_player_pos(int x, int y, char c)
{
	if (g_cube.curr_map.p_dir.x)
		return (handle_file_errors("Multiple player spawn"));
	g_cube.curr_map.p_pos.x = x + 0.5;
	g_cube.curr_map.p_pos.y = y + 0.5;
	if (c == 'N')
	{
		g_cube.curr_map.p_dir.x = cos(3 * M_PI / 2 + 0.001);
		g_cube.curr_map.p_dir.y = sin(3 * M_PI / 2 + 0.001);
	}
	else if (c == 'S')
	{
		g_cube.curr_map.p_dir.x = cos(M_PI / 2 + 0.001);
		g_cube.curr_map.p_dir.y = sin(M_PI / 2 + 0.001);
	}
	else if (c == 'E')
	{
		g_cube.curr_map.p_dir.x = cos(M_PI + 0.001);
		g_cube.curr_map.p_dir.y = sin(M_PI + 0.001);
	}
	else if (c == 'W')
	{
		g_cube.curr_map.p_dir.x = cos(0.001);
		g_cube.curr_map.p_dir.y = sin(0.001);
	}
	return (1);
}

static int	allocate_map(int width, int height)
{
	int	i;

	g_cube.curr_map.map = malloc(sizeof(short int *) * height);
	i = 0;
	while (i < height)
	{
		g_cube.curr_map.map[i] = malloc(sizeof(short int) * width);
		i++;
		//Catch les erreurs de malloc ici please
	}
	return (1);
}

static int add_new_door_pos(char c, int x, int y)
{
	t_obj *new;

	new = malloc(sizeof(t_obj));
	if (!new)
		return (handle_file_errors("parsing door"));
	new->pos.x = x + 0.5;
	new->pos.y = y + 0.5;
	new->start_pos.x = new->pos.x;
	new->start_pos.y = new->pos.y;
	new->bool_move = 0;
	if (c == '|')
	{
		new->type = v_door;
		new->move_dir.x = 0;
		new->move_dir.y = 1;
	}
	else
	{
		new->type = h_door;
		new->move_dir.x = -1;
		new->move_dir.y = 0;
	}
	new->txtr = g_cube.curr_map.door;
	if (!g_cube.curr_map.obj)
		new->id = 0;
	else
		new->id = g_cube.curr_map.obj->id + 1;
	new->next = g_cube.curr_map.obj;
	g_cube.curr_map.obj = new;
	return (1);
}

static int add_new_obj_pos(char c, int x, int y)
{
	t_obj *new;
	t_obj *ptr;

	new = malloc(sizeof(t_obj));
	if (!new)
		return (handle_file_errors("parsing object"));
	new->pos.x = x + 0.5;
	new->pos.y = y + 0.5;
	new->start_pos.x = new->pos.x;
	new->start_pos.y = new->pos.y;
	new->move_dir.x = 0;
	new->move_dir.y = 0;
	ptr = g_cube.curr_map.obj;
	while (ptr)
	{
		if (ptr->c_id == c)
		{
			new->txtr = ptr->txtr;
			break ;
		}
		ptr = ptr->next;
	}
	if (!ptr)
	{
		free(new);
		return (handle_file_errors("unable to create obj"));
	}
	if (!g_cube.curr_map.obj)
		new->id = 0;
	else
		new->id = g_cube.curr_map.obj->id + 1;
	new->next = g_cube.curr_map.obj;
	g_cube.curr_map.obj = new;
	return (1);
}

static int	is_door(char c)
{
	return (c == '|' || c == '-');
}

static int	is_obj(char c)
{
	t_obj *ptr;

	ptr = g_cube.curr_map.obj;
	while (ptr)
	{
		if (c == ptr->c_id)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

static int	fill_map_line(char *line, int height)
{
	int	i;

	i = 0;
	while (line[i])
	{

		if (line[i] == ' ')
			g_cube.curr_map.map[height][i] = -1;
		else if (line[i] >= '0' && line[i] <= '9')
			g_cube.curr_map.map[height][i] = line[i] - '0';
		else if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
				|| line[i] == 'W') && add_player_pos(i, height, line[i]))
			g_cube.curr_map.map[height][i] = 0;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			return (0);
		else if (is_door(line[i]) && add_new_door_pos(line[i], i, height))
			g_cube.curr_map.map[height][i] = 0;
		else if (is_obj(line[i]) &&add_new_obj_pos(line[i], i, height))
			g_cube.curr_map.map[height][i] = 0;
		else
			return (handle_file_errors("Invalid caractere in the map"));
		i++;
	}
	while (i < g_cube.curr_map.map_width)
		g_cube.curr_map.map[height][i++] = -1;
	return (1);
}

int	try_parse_map(int fd, char *line, int width, int height)
{
	char	*next_line;

	if (!line)
	{
		g_cube.curr_map.map_width = width;
		g_cube.curr_map.map_height = height;
		return (allocate_map(width, height));
	}
	if ((int)ft_strlen(line) > width)
		width = ft_strlen(line);
	get_next_line(fd, &next_line);
	if (!try_parse_map(fd, next_line, width, height + 1))
	{
		free(next_line);
		return (0);
	}
	free(next_line);
	return (fill_map_line(line, height));
}
