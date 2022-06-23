#include "cub3D.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int		try_create_map_from_file(char *pathfile)
{
	int		fd;
	char	*line;
	int		valid_file;

	valid_file = 0;
	if (ft_strcmp(ft_strrchr(pathfile, "."), ".cub"))
		return (0);
	fd = open(pathfile, O_RDONLY);
	if (fd == -1)
	{
		handle_errors(pathfile);
		return (0);
	}
	while (get_next_line(fd, &line))
	{

	}
}

void	move_left()
{
	g_cube.curr_map.p_pos.x -= g_cube.curr_map.p_dir.y;
	g_cube.curr_map.p_pos.y -= g_cube.curr_map.p_dir.x;
}

void	move_right()
{
	g_cube.curr_map.p_pos.x += g_cube.curr_map.p_dir.y;
	g_cube.curr_map.p_pos.y += g_cube.curr_map.p_dir.x;
}

void	move_forward()
{
	g_cube.curr_map.p_pos.x += g_cube.curr_map.p_dir.x;
	g_cube.curr_map.p_pos.y += g_cube.curr_map.p_dir.y;
}

void	move_backward()
{
	g_cube.curr_map.p_pos.x -= g_cube.curr_map.p_dir.x;
	g_cube.curr_map.p_pos.y -= g_cube.curr_map.p_dir.y;
}

void	rotate_left()
{
	
}

void	rotate_right()
{
	
}

void	handle_errors(char *str)
{
	(void)str;
	return ;
}

int	key_press_hook(int keycode)
{

	printf("Key pressed : %d\n", keycode);
	if( keycode == K_Q)
		bit_set(g_cube.key_state, B_Q);
	else if( keycode == K_S)
		bit_set(g_cube.key_state, B_S);
	else if( keycode == K_D)
		bit_set(g_cube.key_state, B_D);
	else if( keycode == K_Z)
		bit_set(g_cube.key_state, B_Z);
	else if( keycode == K_A_LEFT)
		bit_set(g_cube.key_state, B_A_LEFT);
	else if( keycode == K_A_RIGHT)
		bit_set(g_cube.key_state, B_A_RIGHT);
	else if (keycode == 53)
	{
		mlx_destroy_image(g_cube.mlx, g_cube.img);
		mlx_destroy_window(g_cube.mlx, g_cube.win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int key_release_hook(int keycode)
{
	printf("Key released : %d\n", keycode);
	if( keycode == K_Q)
		bit_unset(g_cube.key_state, B_Q);
	else if( keycode == K_S)
		bit_unset(g_cube.key_state, B_S);
	else if( keycode == K_D)
		bit_unset(g_cube.key_state, B_D);
	else if( keycode == K_Z)
		bit_unset(g_cube.key_state, B_Z);
	else if( keycode == K_A_LEFT)
		bit_unset(g_cube.key_state, B_A_LEFT);
	else if( keycode == K_A_RIGHT)
		bit_unset(g_cube.key_state, B_A_RIGHT);
	return (0);
}

void	update_cube()
{
	if (bit_is_set(g_cube.key_state, B_Q))
		move_left();
	else if (bit_is_set(g_cube.key_state, B_D))
		move_right();
	else if (bit_is_set(g_cube.key_state, B_S))
		move_backward();
	else if (bit_is_set(g_cube.key_state, B_Z))
		move_forward();
	else if (bit_is_set(g_cube.key_state, B_A_LEFT))
		rotate_left();
	else if (bit_is_set(g_cube.key_state, B_A_RIGHT))
		rotate_right();
}

int	loop_hook()
{
	update_cube();
	//g_cube.display();
	return (0);
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
	{
		handle_errors("Not enough argument");
		return (2);
	}
	if( !try_create_map_from_file(av[1]))
	{

	}
	g_cube.key_state = 0;
	g_cube.resX = 960;
	g_cube.resY = 720;
	g_cube.mlx = mlx_init();
	g_cube.win = mlx_new_window(g_cube.mlx, g_cube.resX, g_cube.resY, "42-Cube3D");
	g_cube.img = mlx_new_image(g_cube.mlx, g_cube.resX, g_cube.resY);
	mlx_hook(g_cube.win, 2, 1L << 0, key_press_hook, NULL);
	mlx_hook(g_cube.win, 3, 1L << 1, key_release_hook, NULL);
	mlx_loop_hook(g_cube.mlx, loop_hook, NULL);
	mlx_loop(g_cube.mlx);
	return (0);
}