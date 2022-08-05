#include "cub3D.h"
#include "libft.h"
#include "mlx.h"

static int	add_color(int *color, char *info)
{
	char	**spl_col;
	int		r;
	int		g;
	int		b;

	spl_col = ft_split(info, ',');
	if (!spl_col[0] || !spl_col[1] || !spl_col[2] || spl_col[3]
		|| !ft_strisdigit(spl_col[0]) || !ft_strisdigit(spl_col[1])
		|| !ft_strisdigit(spl_col[2]))
	{
		free_tab(spl_col);
		return (handle_file_errors("Invlalid color element declaration"));
	}
	r = ft_atoi(spl_col[0]);
	g = ft_atoi(spl_col[1]);
	b = ft_atoi(spl_col[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_tab(spl_col);
		return (handle_file_errors("Invlalid color range value"));
	}
	*color = r << 16 | g << 8 | b;
	free_tab(spl_col);
	return (1);
}

static int	add_wall_texture(t_mlx_img *img, char *info)
{
	if (!img)
		return (handle_file_errors("Double declaration of an wall element"));
	img->img_ptr = mlx_xpm_file_to_image(g_cube.mlx, info, \
		&img->img_width, &img->img_height);
	if (!img->img_ptr)
		return (handle_file_errors("Unable to open xpm file"));
	img->buffer = mlx_get_data_addr(img->img_ptr, &img->bpp, \
		&img->sl, &img->endian);
	return (1);
}

static int	add_element(char **info)
{
	if (!info[1] || info[2])
	{
		return (handle_file_errors("Invalid element line"));
		return (0);
	}
	if (!ft_strncmp(info[0], "NO", 3))
		return (add_wall_texture(&g_cube.curr_map.n_wall, info[1]));
	else if (!ft_strncmp(info[0], "SO", 3))
		return (add_wall_texture(&g_cube.curr_map.s_wall, info[1]));
	else if (!ft_strncmp(info[0], "WE", 3))
		return (add_wall_texture(&g_cube.curr_map.w_wall, info[1]));
	else if (!ft_strncmp(info[0], "EA", 3))
		return (add_wall_texture(&g_cube.curr_map.e_wall, info[1]));
	else if (!ft_strncmp(info[0], "F", 2))
		return (add_color(&g_cube.curr_map.floor_color, info[1]));
	else if (!ft_strncmp(info[0], "C", 2))
		return (add_color(&g_cube.curr_map.cell_color, info[1]));
	else
		return (handle_file_errors("Invalid element keyname"));
}

static int	is_map(char *line)
{
	while (*line == ' ')
		line++;
	if (*line == '0' || *line == '1')
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
