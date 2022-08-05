#include "cub3D.h"

static int	is_map_closed(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < g_cube.curr_map.map_height)
	{
		j = 0;
		while (j < g_cube.curr_map.map_width)
		{
			if (g_cube.curr_map.map[i][j] == 0
				&& (i == 0 || i == g_cube.curr_map.map_height - 1
				|| j == 0 || j == g_cube.curr_map.map_width - 1
				|| g_cube.curr_map.map[i - 1][j] == -1
				|| g_cube.curr_map.map[i + 1][j] == -1
				|| g_cube.curr_map.map[i][j + 1] == -1
				|| g_cube.curr_map.map[i][j - 1] == -1))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	set_valid_map_value(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < g_cube.curr_map.map_height)
	{
		j = 0;
		while (j < g_cube.curr_map.map_width)
		{
			if (g_cube.curr_map.map[i][j] == -1)
				g_cube.curr_map.map[i][j] = 0;
			j++;
		}
		i++;
	}
}

int	is_valid_map(void)
{
	if (!g_cube.curr_map.p_dir.x)
		return (handle_file_errors("Missing player init position"));
	if (!is_map_closed())
		return (handle_file_errors("Empty blocks are not surrounded by walls"));
	set_valid_map_value();
	return (1);
}
