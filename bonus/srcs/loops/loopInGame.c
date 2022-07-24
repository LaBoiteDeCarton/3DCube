#include "cub3D.h"
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
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
	else if ( keycode == K_M)
		loopMenu();
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

static void	borders(t_mlx_img image)
{
	int adress;

	adress = -1;
	while (++adress < (image.sl / 4) * 2)
		((unsigned int *)image.buffer)[adress] = 0x00555555;
	adress = (image.sl / 4) * 2;
	while (adress < (image.sl / 4) * image.img_height)
	{	
		((unsigned int *)image.buffer)[adress] = 0x00555555;
		((unsigned int *)image.buffer)[adress + 1] = 0x00555555;
		((unsigned int *)image.buffer)[adress - 1] = 0x00aaaaaa;
		((unsigned int *)image.buffer)[adress - 2] = 0x00aaaaaa;
		adress += image.sl / 4;
	}
	adress = (image.sl / 4) * (image.img_height - 2);
	while (++adress <= (image.sl / 4) * (image.img_height))
		((unsigned int *)image.buffer)[adress - 1] = 0x00aaaaaa;
}

void	fill_image(t_mlx_img img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < img.img_height)
	{
		x = 0;
		while (x < img.img_width)
		{
			((unsigned int *)img.buffer)[y * (img.sl / 4) + x] = color;
			x++;
		}
		y++;
	}
}

void	display_miniMap()
{
	t_mlx_img img;
	t_vect	p_pos;
	int x;
	int	y;
	int i;

	img.img_height = (RES_HEIGHT - 50) / 5;
	img.img_width = (RES_HEIGHT - 50) / 5;
	img.img_ptr = mlx_new_image(g_cube.mlx, img.img_height, img.img_width);
	img.buffer = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.sl, &img.endian);
	fill_image(img, 0x00323232);
	((unsigned int *)img.buffer)[img.img_height / 2 * (img.sl / 4) + img.img_width / 2] = 0x00883030;
	((unsigned int *)img.buffer)[img.img_height / 2 * (img.sl / 4) + img.img_width / 2 - 1] = 0x00883030;
	((unsigned int *)img.buffer)[img.img_height / 2 * (img.sl / 4) + img.img_width / 2 + 1] = 0x00883030;
	((unsigned int *)img.buffer)[(img.img_height / 2 - 1) * (img.sl / 4) + img.img_width / 2] = 0x00883030;
	((unsigned int *)img.buffer)[(img.img_height / 2 + 1) * (img.sl / 4) + img.img_width / 2] = 0x00883030;
	p_pos.x = img.img_width / 2;
	p_pos.y = img.img_height / 2;
	i = 0;
	while (i < 100)
	{
		p_pos.x += g_cube.curr_map.p_dir.x/10;
		p_pos.y += g_cube.curr_map.p_dir.y/10;
		((unsigned int *)img.buffer)[(int)p_pos.y * (img.sl / 4) + (int)p_pos.x] = 0x00883030;
		i++;
	}
	y = 0;
	while (y < img.img_height)
	{
		x = 0;
		while (x < img.img_width)
		{
			if (floorf(g_cube.curr_map.p_pos.y - (float)img.img_height / 20 + (float)y / 10) >= 0.
				&& (int)(g_cube.curr_map.p_pos.y - (float)img.img_height / 20 + (float)y / 10) < g_cube.curr_map.map_height
				&& floorf(g_cube.curr_map.p_pos.x - (float)img.img_width / 20 + (float)x / 10) >= 0.
				&& (int)(g_cube.curr_map.p_pos.x - (float)img.img_width / 20 + (float)x / 10) < g_cube.curr_map.map_width
				&& g_cube.curr_map.map[(int)(g_cube.curr_map.p_pos.y - (float)img.img_height / 20 + (float)y / 10)][(int)(g_cube.curr_map.p_pos.x - (float)img.img_width / 20 + (float)x / 10)])
				((unsigned int *)img.buffer)[y * (img.sl / 4) + x] = 0x0066AABB;
			x++;
		}
		y++;
	}
	
	borders(img);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, img.img_ptr, RES_WIDTH - 25 - img.img_width, RES_HEIGHT * 4 / 5);
	mlx_destroy_image(g_cube.mlx, img.img_ptr);
}

static void	fill_cell_floor()
{
	int		adress;

	adress = -1;
	while (++adress < (g_cube.img_raycast.sl / 4) * g_cube.img_raycast.img_height / 2)
		((unsigned int *)g_cube.img_raycast.buffer)[adress] = g_cube.curr_map.cell_color;
	while (adress++ <= (g_cube.img_raycast.sl / 4) * (g_cube.img_raycast.img_height))
		((unsigned int *)g_cube.img_raycast.buffer)[adress] = g_cube.curr_map.floor_color;
}

static void	fill_background()
{
	t_mlx_img	img;
	int			adress;

	img.img_ptr = mlx_new_image(g_cube.mlx, RES_WIDTH, RES_HEIGHT);
	img.buffer = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.sl, &img.endian);
	adress = -1;
	while (++adress <= (img.sl / 4) * (RES_HEIGHT))
		((unsigned int *)img.buffer)[adress - 1] = 0x00bbbbbb;
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, img.img_ptr, 0, 0);
	mlx_destroy_image(g_cube.mlx, img.img_ptr);
}

static void	create_raycast_img()
{
	g_cube.img_raycast.img_width = RES_WIDTH - 50;
	g_cube.img_raycast.img_height = (RES_HEIGHT - 50) * 4 / 5;
	g_cube.img_raycast.img_ptr = mlx_new_image(g_cube.mlx, g_cube.img_raycast.img_width, g_cube.img_raycast.img_height);
	g_cube.img_raycast.buffer = mlx_get_data_addr(g_cube.img_raycast.img_ptr, &g_cube.img_raycast.bpp, &g_cube.img_raycast.sl, &g_cube.img_raycast.endian);
	fill_cell_floor();
	raycast(g_cube.img_raycast);
	borders(g_cube.img_raycast);
}

#include "libft.h"

static int	loop_hook()
{
	update_cube_data();
	fill_background();
	create_raycast_img();
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.img_raycast.img_ptr, 25, 25);
	mlx_destroy_image(g_cube.mlx, g_cube.img_raycast.img_ptr);
	display_miniMap();
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