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
		g_cube.curr_map.p_dir.x = cos(3 * M_PI / 2 + 0.0001);
		g_cube.curr_map.p_dir.y = sin(3 * M_PI / 2 + 0.0001);
	}
	else if (c == 'S')
	{
		g_cube.curr_map.p_dir.x = cos(M_PI / 2 + 0.0001);
		g_cube.curr_map.p_dir.y = sin(M_PI / 2 + 0.0001);
	}
	else if (c == 'E')
	{
		g_cube.curr_map.p_dir.x = cos(M_PI + 0.0001);
		g_cube.curr_map.p_dir.y = sin(M_PI + 0.0001);
	}
	else if (c == 'W')
	{
		g_cube.curr_map.p_dir.x = cos(0.0001);
		g_cube.curr_map.p_dir.y = sin(0.0001);
	}
	return (1);
}

static int	allocate_map(int width, int height)
{
	int	i;

	g_cube.curr_map.map = malloc(sizeof(short int *) * height);
	if (!g_cube.curr_map.map)
	{
		handle_errors("parsing error");
		return (0);
	}
	i = 0;
	while (i < height)
	{
		g_cube.curr_map.map[i] = malloc(sizeof(short int) * width);
		if (!g_cube.curr_map.map[i])
		{
			while (--i >= 0)
				free(g_cube.curr_map.map[i]);
			free(g_cube.curr_map.map);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	fill_map_line(char *line, int height)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0')
			g_cube.curr_map.map[height][i] = 0;
		else if (line[i] == '1')
			g_cube.curr_map.map[height][i] = 1;
		else if (line[i] == ' ')
			g_cube.curr_map.map[height][i] = -1;
		else if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
				|| line[i] == 'W') && add_player_pos(i, height, line[i]))
			g_cube.curr_map.map[height][i] = 0;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			return (0);
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
