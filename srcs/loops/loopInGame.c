#include "cub3D.h"
#include <fcntl.h>
#include <stdlib.h>
#include "mlx.h"

static int	key_press_hook(int keycode)
{

	//printf("Key pressed : %d\n", keycode);
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
		cube_exit();
	return (0);
}

static int key_release_hook(int keycode)
{
	// printf("Key released : %d\n", keycode);
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

static void	update_cube()
{
	if (bit_is_set(g_cube.key_state, B_Q))
		move_left();
	if (bit_is_set(g_cube.key_state, B_D))
		move_right();
	if (bit_is_set(g_cube.key_state, B_S))
		move_backward();
	if (bit_is_set(g_cube.key_state, B_Z))
		move_forward();
	if (bit_is_set(g_cube.key_state, B_A_LEFT))
		rotate_left();
	if (bit_is_set(g_cube.key_state, B_A_RIGHT))
		rotate_right();
}

void	display_miniMap()
{
	// for (int i = 0; i < 10; i++)
	// {
	// 	for (int j = 0; j < 10; j++)
	// 	if (g_cube.curr_map.map[i][j] == 1)
	// 		mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.wall.ptr, j * g_cube.wall.img_width, i * g_cube.wall.img_height);
	// }
	// mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.wall.ptr, g_cube.curr_map.p_pos.x * g_cube.wall.img_width, g_cube.curr_map.p_pos.y * g_cube.wall.img_height);
	// mlx_string_put(g_cube.mlx, g_cube.win, 100, 100, 125, "HELLO how are you?");
}

static int	loop_hook()
{
	update_cube();
	display_miniMap();
	return (0);
}

void	loopInGame()
{
	mlx_do_key_autorepeatoff(g_cube.mlx);
	mlx_hook(g_cube.win, 2, 1L << 0, key_press_hook, NULL);
	//mlx_hook(g_cube.win, 2, 1L << 0, key_press_hook2, NULL); overide l'event
	mlx_hook(g_cube.win, 3, 1L << 1, key_release_hook, NULL);
	mlx_loop_hook(g_cube.mlx, loop_hook, NULL);
}