#include "cub3D.h"
#include "mlx.h"
#include "libft.h"
#include <fcntl.h>

static int	try_open_file(char *pathfile)
{
	int		fd;

	if (ft_strncmp(ft_strrchr(pathfile, '.'), ".cub", 5))
	{
		handle_file_errors("Invalid file type");
		return (-1);
	}
	fd = open(pathfile, O_RDONLY);
	if (fd == -1)
	{
		handle_errors(pathfile);
		return (-1);
	}
	return (fd);
}

int	try_parse_file(char *pathfile)
{
	int		fd;
	char	*line;

	fd = try_open_file(pathfile);
	if (fd == -1)
		return (0);
	if (!try_parse_element(fd, &line))
	{
		close(fd);
		return (0);
	}
	if (!try_parse_map(fd, line, 0, 0))
	{
		free(line);
		close(fd);
		return (0);
	}
	free(line);
	close(fd);
	g_cube.curr_map.max_collect = 3;
	return (is_valid_map());
}
