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
		cube_exit(EXIT_SUCCESS);
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

static void	update_cube_data()
{
	int	x_mouse;
	int	y_mouse;

	if (bit_is_set(g_cube.key_state, B_Q) && ! bit_is_set(g_cube.key_state, B_D))
		move_left();
	if (bit_is_set(g_cube.key_state, B_D) && ! bit_is_set(g_cube.key_state, B_Q))
		move_right();
	if (bit_is_set(g_cube.key_state, B_S) && ! bit_is_set(g_cube.key_state, B_Z))
		move_backward();
	if (bit_is_set(g_cube.key_state, B_Z) && ! bit_is_set(g_cube.key_state, B_S))
		move_forward();
	if (bit_is_set(g_cube.key_state, B_A_LEFT) && ! bit_is_set(g_cube.key_state, B_A_RIGHT))
		rotate_left();
	if (bit_is_set(g_cube.key_state, B_A_RIGHT) && ! bit_is_set(g_cube.key_state, B_A_LEFT))
		rotate_right();
	mlx_mouse_get_pos(g_cube.win, &x_mouse, &y_mouse);
	mlx_mouse_move(g_cube.win, RES_WIDTH / 2, RES_HEIGHT / 2);
	rotate((x_mouse - (RES_WIDTH / 2)) * 0.005);
}

static void	fill_cell_floor()
{
	int		adress;

	adress = -1;
	while (++adress < (g_cube.img_onload.sl / 4) * RES_HEIGHT / 2)
		((unsigned int *)g_cube.img_onload.buffer)[adress] = g_cube.curr_map.cell_color;
	while (adress++ < (g_cube.img_onload.sl / 4) * (RES_HEIGHT - 1))
		((unsigned int *)g_cube.img_onload.buffer)[adress] = g_cube.curr_map.floor_color;
}

static int	loop_hook()
{
	update_cube_data();
	g_cube.img_onload.img_ptr = mlx_new_image(g_cube.mlx, RES_WIDTH, RES_HEIGHT);
	g_cube.img_onload.buffer = mlx_get_data_addr(g_cube.img_onload.img_ptr, &g_cube.img_onload.bpp, &g_cube.img_onload.sl, &g_cube.img_onload.endian);
	fill_cell_floor();
	raycast();
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.img_onload.img_ptr, 0, 0);
	mlx_destroy_image(g_cube.mlx, g_cube.img_onscreen.img_ptr);
	g_cube.img_onscreen.img_ptr = g_cube.img_onload.img_ptr;
	g_cube.img_onload.img_ptr = NULL;
	return (0);
}

void	loopInGame()
{
	mlx_do_key_autorepeatoff(g_cube.mlx);
	mlx_mouse_move(g_cube.win, RES_WIDTH / 2, RES_HEIGHT / 2);
	mlx_mouse_hide();
	mlx_hook(g_cube.win, 2, 1L << 0, key_press_hook, NULL);
	mlx_hook(g_cube.win, 3, 1L << 1, key_release_hook, NULL);
	mlx_loop_hook(g_cube.mlx, loop_hook, NULL);
}