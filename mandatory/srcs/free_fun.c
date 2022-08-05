#include "cub3D.h"
#include <stdlib.h>

void	free_tab(char **chartab)
{
	int	i;

	i = 0;
	if (!chartab)
		return ;
	while (chartab[i])
		free(chartab[i++]);
	free(chartab);
}

void	free_map(void)
{
	int	i;

	i = 0;
	if (!g_cube.curr_map.map)
		return ;
	while (i < g_cube.curr_map.map_height)
	{
		if (g_cube.curr_map.map[i])
			free(g_cube.curr_map.map[i]);
		i++;
	}
	free(g_cube.curr_map.map);
}
