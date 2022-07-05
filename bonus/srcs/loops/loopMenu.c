#include "cub3D.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include "mlx.h"
#include <stdio.h>
# define GENERIC_MAX(x, y) ((x) > (y) ? (x) : (y))

void	change_res_to_small()
{
	return ;
}
void	change_res_to_big()
{
	return ;
}

static void	menu_select()
{
	if (g_cube.menu.menu_curr == menu && g_cube.menu.select == 2)
		cube_exit();
	if (g_cube.menu.menu_curr == menu && g_cube.menu.select == 0)
		loopInGame();
	if (g_cube.menu.menu_curr == menu && g_cube.menu.select == 1)
		g_cube.menu.menu_curr = config;
	if (g_cube.menu.menu_curr == config && g_cube.menu.select == 2)
		g_cube.menu.menu_curr = menu;
	if (g_cube.menu.menu_curr == config && g_cube.menu.select == 0)
		change_res_to_small();
	if (g_cube.menu.menu_curr == config && g_cube.menu.select == 1)
		change_res_to_big();
}

static int	key_press_hook(int keycode)
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

static int key_release_hook(int keycode)
{
	(void)keycode;
	return (0);
}

char	*get_str(t_btn_content content)
{
	if (content == menu)
		return (ft_strdup("menu"));
	if (content == play)
		return (ft_strdup("play"));
	if (content == quit)
		return (ft_strdup("quit"));
	if (content == select_level)
		return (ft_strdup("select_level"));
	if (content == retry)
		return (ft_strdup("retry"));
	if (content == back)
		return (ft_strdup("back"));
	if (content == config)
		return (ft_strdup("config"));
	return (ft_strdup("none"));
}

void	display_menu()
{
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_bg.ptr, 0, 0);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_btn_off.ptr, RES_WIDTH/2 - g_cube.menu.menu_btn_off.img_width / 2, 200 + 1 * 100 - g_cube.menu.menu_btn_off.img_height / 2);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_btn_off.ptr, RES_WIDTH/2 - g_cube.menu.menu_btn_off.img_width / 2, 200 + 2 * 100 - g_cube.menu.menu_btn_off.img_height / 2);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_btn_off.ptr, RES_WIDTH/2 - g_cube.menu.menu_btn_off.img_width / 2, 200 + 3 * 100 - g_cube.menu.menu_btn_off.img_height / 2);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_btn_on.ptr, RES_WIDTH/2 - g_cube.menu.menu_btn_on.img_width / 2, 200 + (1 + g_cube.menu.select) * 100 - g_cube.menu.menu_btn_on.img_height / 2);
	mlx_string_put(g_cube.mlx, g_cube.win, RES_WIDTH/2 - 15, 200 + 5, 0x00babc, "menu");
	mlx_string_put(g_cube.mlx, g_cube.win, RES_WIDTH/2 - 15, 200 + 1 * 100 + 5, 0x00babc, "play");
	mlx_string_put(g_cube.mlx, g_cube.win, RES_WIDTH/2 - 60, 200 + 2 * 100 + 5, 0x00babc, "graphic options");
	mlx_string_put(g_cube.mlx, g_cube.win, RES_WIDTH/2 - 15, 200 + 3 * 100 + 5, 0x00babc, "quit");
}

void	display_graphic()
{
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_bg.ptr, 0, 0);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_btn_off.ptr, RES_WIDTH/2 - g_cube.menu.menu_btn_off.img_width / 2, 200 + 1 * 100 - g_cube.menu.menu_btn_off.img_height / 2);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_btn_off.ptr, RES_WIDTH/2 - g_cube.menu.menu_btn_off.img_width / 2, 200 + 2 * 100 - g_cube.menu.menu_btn_off.img_height / 2);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_btn_off.ptr, RES_WIDTH/2 - g_cube.menu.menu_btn_off.img_width / 2, 200 + 3 * 100 - g_cube.menu.menu_btn_off.img_height / 2);
	mlx_put_image_to_window(g_cube.mlx, g_cube.win, g_cube.menu.menu_btn_on.ptr, RES_WIDTH/2 - g_cube.menu.menu_btn_on.img_width / 2, 200 + (1 + g_cube.menu.select) * 100 - g_cube.menu.menu_btn_on.img_height / 2);
	mlx_string_put(g_cube.mlx, g_cube.win, RES_WIDTH/2 - 75, 200 + 5, 0x00babc, "graphic options");
	mlx_string_put(g_cube.mlx, g_cube.win, RES_WIDTH/2 - 35, 200 + 1 * 100 + 5, 0x00babc, "640x480");
	mlx_string_put(g_cube.mlx, g_cube.win, RES_WIDTH/2 - 35, 200 + 2 * 100 + 5, 0x00babc, "960x720");
	mlx_string_put(g_cube.mlx, g_cube.win, RES_WIDTH/2 - 20, 200 + 3 * 100 + 5, 0x00babc, "back");
}

static int	loop_hook()
{
	if (g_cube.menu.menu_curr == menu)
		display_menu();
	if (g_cube.menu.menu_curr == config)
		display_graphic();
	return (0);
}

void	loopMenu()
{
	mlx_hook(g_cube.win, 2, 1L << 0, key_press_hook, NULL);
	mlx_hook(g_cube.win, 3, 1L << 1, key_release_hook, NULL);
	mlx_loop_hook(g_cube.mlx, loop_hook, NULL);
}