#include "cub3D.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include "mlx.h"
#include <stdio.h>
# define GENERIC_MAX(x, y) ((x) > (y) ? (x) : (y))

void menu_select();

int key_release_hook(int keycode)
{
	(void)keycode;
	return (0);
}

int	key_press_hook(int keycode)
{
	printf("Key pressed : %d\n", keycode);
	if( keycode == K_A_UP)
		g_cube.menu.select--;
	else if( keycode == K_A_DOWN)
		g_cube.menu.select++;
	else if( keycode == K_ENTER)
		menu_select();
	else if (keycode == 53)
		cube_exit(EXIT_SUCCESS);
	if (g_cube.menu.select < 0)	
		g_cube.menu.select = 0;
	if (g_cube.menu.select > 2)
		g_cube.menu.select = 2;
	return (0);
}

void	change_res_to_small()
{
	g_cube.res_width = 640;
	g_cube.res_height = 480;
	mlx_destroy_window(g_cube.mlx, g_cube.win);
	g_cube.win = mlx_new_window(g_cube.mlx, g_cube.res_width, g_cube.res_height, "42-Cube3D");
	loopMenu();
	return ;
}
void	change_res_to_big()
{
	g_cube.res_width = 960;
	g_cube.res_height = 720;
	mlx_destroy_window(g_cube.mlx, g_cube.win);
	g_cube.win = mlx_new_window(g_cube.mlx, g_cube.res_width, g_cube.res_height, "42-Cube3D");
	loopMenu();
	return ;
}

void	menu_select()
{
	if (g_cube.menu.menu_curr == menu && g_cube.menu.select == 2)
		cube_exit(0);
	else if (g_cube.menu.menu_curr == menu && g_cube.menu.select == 0)
		loopInGame();
	else if (g_cube.menu.menu_curr == menu && g_cube.menu.select == 1)
		g_cube.menu.menu_curr = config;
	else if (g_cube.menu.menu_curr == config && g_cube.menu.select == 2)
		g_cube.menu.menu_curr = menu;
	else if (g_cube.menu.menu_curr == config && g_cube.menu.select == 0)
		change_res_to_small();
	else if (g_cube.menu.menu_curr == config && g_cube.menu.select == 1)
		change_res_to_big();
}

void	display_menu()
{
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_bg.img_ptr, 0, 0);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_btn_off.img_ptr, g_cube.res_width/2 - g_cube.menu.menu_btn_off.img_width / 2, 200 + 1 * 100 - g_cube.menu.menu_btn_off.img_height / 2);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_btn_off.img_ptr, g_cube.res_width/2 - g_cube.menu.menu_btn_off.img_width / 2, 200 + 2 * 100 - g_cube.menu.menu_btn_off.img_height / 2);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_btn_off.img_ptr, g_cube.res_width/2 - g_cube.menu.menu_btn_off.img_width / 2, 200 + 3 * 100 - g_cube.menu.menu_btn_off.img_height / 2);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_btn_on.img_ptr, g_cube.res_width/2 - g_cube.menu.menu_btn_on.img_width / 2, 200 + (1 + g_cube.menu.select) * 100 - g_cube.menu.menu_btn_on.img_height / 2);
	mlx_string_put(g_cube.mlx, g_cube.win, g_cube.res_width/2 - 15, 200 + 5, 0x00babc, "menu");
	mlx_string_put(g_cube.mlx, g_cube.win, g_cube.res_width/2 - 15, 200 + 1 * 100 + 5, 0x00babc, "play");
	mlx_string_put(g_cube.mlx, g_cube.win, g_cube.res_width/2 - 60, 200 + 2 * 100 + 5, 0x00babc, "graphic options");
	mlx_string_put(g_cube.mlx, g_cube.win, g_cube.res_width/2 - 15, 200 + 3 * 100 + 5, 0x00babc, "quit");
}

void	display_graphic()
{
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_bg.img_ptr, 0, 0);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_btn_off.img_ptr, g_cube.res_width/2 - g_cube.menu.menu_btn_off.img_width / 2, 200 + 1 * 100 - g_cube.menu.menu_btn_off.img_height / 2);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_btn_off.img_ptr, g_cube.res_width/2 - g_cube.menu.menu_btn_off.img_width / 2, 200 + 2 * 100 - g_cube.menu.menu_btn_off.img_height / 2);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_btn_off.img_ptr, g_cube.res_width/2 - g_cube.menu.menu_btn_off.img_width / 2, 200 + 3 * 100 - g_cube.menu.menu_btn_off.img_height / 2);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_btn_on.img_ptr, g_cube.res_width/2 - g_cube.menu.menu_btn_on.img_width / 2, 200 + (1 + g_cube.menu.select) * 100 - g_cube.menu.menu_btn_on.img_height / 2);
	mlx_string_put(g_cube.mlx, g_cube.win, g_cube.res_width/2 - 75, 200 + 5, 0x00babc, "graphic options");
	mlx_string_put(g_cube.mlx, g_cube.win, g_cube.res_width/2 - 35, 200 + 1 * 100 + 5, 0x00babc, "640x480");
	mlx_string_put(g_cube.mlx, g_cube.win, g_cube.res_width/2 - 35, 200 + 2 * 100 + 5, 0x00babc, "960x720");
	mlx_string_put(g_cube.mlx, g_cube.win, g_cube.res_width/2 - 20, 200 + 3 * 100 + 5, 0x00babc, "back");
}

int	loop_hook()
{
	if (g_cube.menu.menu_curr == menu)
		display_menu();
	if (g_cube.menu.menu_curr == config)
		display_graphic();
	return (0);
}

int		close_win()
{
	cube_exit(EXIT_SUCCESS);
	return (1);
}

void	loopMenu()
{
	mlx_do_key_autorepeaton(g_cube.mlx);
	mlx_mouse_show();
	mlx_hook(g_cube.win, 2, 1L << 0, key_press_hook, NULL);
	mlx_hook(g_cube.win, 3, 1L << 1, key_release_hook, NULL);
	mlx_hook(g_cube.win, 17, 0L, &close_win, NULL);
	mlx_loop_hook(g_cube.mlx, loop_hook, NULL);
}