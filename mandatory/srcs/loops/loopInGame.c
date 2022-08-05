#include "cub3D.h"
#include <fcntl.h>
#include <stdlib.h>
#include "mlx.h"

static int	key_press_hook(int keycode)
{
	if (keycode == K_Q)
		(g_cube.key_state |= 1 << B_Q);
	else if (keycode == K_S)
		(g_cube.key_state |= 1 << B_S);
	else if (keycode == K_D)
		(g_cube.key_state |= 1 << B_D);
	else if (keycode == K_Z)
		(g_cube.key_state |= 1 << B_Z);
	else if (keycode == K_A_LEFT)
		(g_cube.key_state |= 1 << B_A_LEFT);
	else if (keycode == K_A_RIGHT)
		(g_cube.key_state |= 1 << B_A_RIGHT);
	else if (keycode == 53)
		cube_exit(EXIT_SUCCESS);
	return (0);
}

static int	key_release_hook(int keycode)
{
	if (keycode == K_Q)
		(g_cube.key_state ^= 1 << B_Q);
	else if (keycode == K_S)
		(g_cube.key_state ^= 1 << B_S);
	else if (keycode == K_D)
		(g_cube.key_state ^= 1 << B_D);
	else if (keycode == K_Z)
		(g_cube.key_state ^= 1 << B_Z);
	else if (keycode == K_A_LEFT)
		(g_cube.key_state ^= 1 << B_A_LEFT);
	else if (keycode == K_A_RIGHT)
		(g_cube.key_state ^= 1 << B_A_RIGHT);
	return (0);
}

static void	update_cube_data(void)
{
	int	x_mouse;
	int	y_mouse;

	if ((g_cube.key_state & 1 << B_Q)
		&& ! (g_cube.key_state & 1 << B_D))
		move_left();
	if ((g_cube.key_state & 1 << B_D)
		&& ! (g_cube.key_state & 1 << B_Q))
		move_right();
	if ((g_cube.key_state & 1 << B_S)
		&& ! (g_cube.key_state & 1 << B_Z))
		move_backward();
	if ((g_cube.key_state & 1 << B_Z)
		&& ! (g_cube.key_state & 1 << B_S))
		move_forward();
	if ((g_cube.key_state & 1 << B_A_LEFT)
		&& ! (g_cube.key_state & 1 << B_A_RIGHT))
		rotate_left();
	if ((g_cube.key_state & 1 << B_A_RIGHT)
		&& ! (g_cube.key_state & 1 << B_A_LEFT))
		rotate_right();
	mlx_mouse_get_pos(g_cube.win, &x_mouse, &y_mouse);
	mlx_mouse_move(g_cube.win, RES_W / 2, RES_H / 2);
	rotate((x_mouse - (RES_W / 2)) * 0.005);
}

static int	loop_hook(void)
{
	t_mlx_img	*img;
	int			adress;

	update_cube_data();
	img = &g_cube.rcimg;
	img->img_ptr = mlx_new_image(g_cube.mlx, RES_W, RES_H);
	img->buffer = mlx_get_data_addr(img->img_ptr, &img->bpp, \
		&img->sl, &img->endian);
	adress = -1;
	while (++adress < (img->sl / 4) * RES_H / 2)
		((int *)img->buffer)[adress] = g_cube.curr_map.cell_color;
	while (adress++ < (img->sl / 4) * (RES_H - 1))
		((int *)img->buffer)[adress] = g_cube.curr_map.floor_color;
	raycast();
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, img->img_ptr, 0, 0);
	mlx_destroy_image(g_cube.mlx, img->img_ptr);
	return (0);
}

void	loopInGame(void)
{
	mlx_do_key_autorepeatoff(g_cube.mlx);
	mlx_mouse_move(g_cube.win, RES_W / 2, RES_H / 2);
	mlx_mouse_hide();
	mlx_hook(g_cube.win, 2, 1L << 0, key_press_hook, NULL);
	mlx_hook(g_cube.win, 3, 1L << 1, key_release_hook, NULL);
	mlx_loop_hook(g_cube.mlx, loop_hook, NULL);
}
