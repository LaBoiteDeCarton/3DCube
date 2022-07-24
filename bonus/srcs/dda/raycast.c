#include "cub3D.h"
#include <unistd.h>
#include <math.h>
#define _USE_MATH_DEFINES

void	set_cam_vect(t_vect *vect)
{
	vect->x = -g_cube.curr_map.p_dir.y;
	vect->y = g_cube.curr_map.p_dir.x;
	vect->x = (vect->x * 2) / (3 * RES_WIDTH / 2);
	vect->y = (vect->y * 2) / (3 * RES_WIDTH / 2);
}

static int	throw_ray_x(t_vect *res, t_vect ray)
{
	double		m;
	int			x;
	double		y; 

	if (ray.x == 0.f)
		return -1;
	if (ray.y == 0.f)
		return -1; // appeler une autre fonction de calcul car cas tres specifique
	m = ray.y / ray.x;
	if (ray.x > 0)
	{
		x = (int)g_cube.curr_map.p_pos.x;
		x++;
		while (x < g_cube.curr_map.map_width) //map_width
		{
			y = m * ((double)x - g_cube.curr_map.p_pos.x) + g_cube.curr_map.p_pos.y;
			if (y < 0 || y >= g_cube.curr_map.map_height) //map_height
				return -1;
			if (g_cube.curr_map.map[(int)y][x] && g_cube.curr_map.map[(int)y][x] < 30)
				break ;
			x++;
		}
		res->x = x;
		res->y = y;
		return (g_cube.curr_map.map[(int)y][x]);
	}
	if (ray.x < 0)
	{
		x = (int)g_cube.curr_map.p_pos.x;
		while (x > 0 && x < g_cube.curr_map.map_width)
		{
			y = m * ((double)x - g_cube.curr_map.p_pos.x) + g_cube.curr_map.p_pos.y;
			if (y < 0 || y >= g_cube.curr_map.map_height) //map_height
				return -1;
			else if (g_cube.curr_map.map[(int)y][x - 1] && g_cube.curr_map.map[(int)y][x - 1] < 30)
				break;
			x--;
		}
		res->x = x;
		res->y = y;
		return (g_cube.curr_map.map[(int)y][x - 1]);
	}
	return (-1);
}

static int	throw_ray_y(t_vect *res, t_vect ray, int old_id)
{
	double		m;
	double		x;
	int			y; 

	if (ray.y == 0.f)
		return old_id;
	if (ray.x == 0.f)
		return old_id; // appeler une autre fonction de calcul car cas tres specifique
	m = ray.x / ray.y;
	if (ray.y > 0)
	{
		y = (int)g_cube.curr_map.p_pos.y;
		y++;
		while (y < g_cube.curr_map.map_height) //map_height
		{
			x = m * ((double)y - g_cube.curr_map.p_pos.y) + g_cube.curr_map.p_pos.x;
			if (x < 0 || x >= g_cube.curr_map.map_width) //map_height
				return old_id;
			else if (g_cube.curr_map.map[y][(int)x] && g_cube.curr_map.map[y][(int)x] < 30)
				break ;
			y++;
		}
		if (res->y == 0.f || y <= res->y)
		{
			res->x = x;
			res->y = y;
			return (g_cube.curr_map.map[y][(int)x]);
		}
		return old_id;
	}
	if (ray.y < 0)
	{
		y = (int)g_cube.curr_map.p_pos.y;
		while (y > 0 && y < g_cube.curr_map.map_height)
		{
			x = m * ((double)y - g_cube.curr_map.p_pos.y) + g_cube.curr_map.p_pos.x;
			if (x < 0 || x >= g_cube.curr_map.map_width) //map_height
				return old_id;
			if (g_cube.curr_map.map[y - 1][(int)x] && g_cube.curr_map.map[y - 1][(int)x] < 30)
				break;
			y--;
		}
		// res->x = x;
		// res->y = y;
		if (y > res->y)
		{
			res->x = x;
			res->y = y;
			return (g_cube.curr_map.map[y - 1][(int)x]);
		}
		return (old_id);
	}
	return (old_id);
}

void	put_coloumn_wall(t_vect *ray, t_vect pos, int wall_id, int coloumn)
{
	double	fraction;
	int		wall_size;
	float	real_x;
	float	real_y;
	int		i;
	int		wall_coloumn;
	int		wall_line;
	t_mlx_img	mlx_img;
	t_walls		*wall_ptr;
	
	wall_ptr = g_cube.curr_map.w_txtr;
	while (wall_ptr && wall_ptr->id != wall_id)
		wall_ptr = wall_ptr->next;
	if (wall_ptr == NULL)
		return ;
	mlx_img = wall_ptr->txtr;
	real_x = pos.x - g_cube.curr_map.p_pos.x;
	real_y = pos.y - g_cube.curr_map.p_pos.y;
	fraction = sqrtf((real_x * real_x + real_y * real_y) / (ray->x * ray->x + ray->y * ray->y));
	wall_size = (int)((float)g_cube.img_raycast.img_width / (2.5 * fraction * tan(M_PI / 6)));
	if (pos.x - floorf(pos.x) < pos.y - floorf(pos.y))
		wall_coloumn = (pos.y - floorf(pos.y)) * mlx_img.img_width;
	else
		wall_coloumn = (pos.x - floorf(pos.x)) * mlx_img.img_width;
	i = (g_cube.img_raycast.img_height / 2) - (wall_size / 2);
	while (i < (g_cube.img_raycast.img_height / 2) + (wall_size / 2))
	{
		wall_line = (int)((float)(i - ((g_cube.img_raycast.img_height / 2) - (wall_size / 2))) * (float)mlx_img.img_height / (float)wall_size);
		if (i < g_cube.img_raycast.img_height && i > 0 && wall_coloumn < mlx_img.img_width && wall_line < mlx_img.img_height)
		{
			if (((unsigned int *)(mlx_img.buffer))[wall_line  * (mlx_img.sl / 4) + wall_coloumn] != 0x000000b0)
				((unsigned int *)g_cube.img_raycast.buffer)[i * (g_cube.img_raycast.sl / 4) + coloumn] = 
					((unsigned int *)(mlx_img.buffer))[wall_line  * (mlx_img.sl / 4) + wall_coloumn];
			else
				((unsigned int *)g_cube.img_raycast.buffer)[i * (g_cube.img_raycast.sl / 4) + coloumn] += 
					0x00000030;
		}

		i++;
	}
}

// void	put_ray(t_vect w_pos, t_vect ray, int print_ray)
// {
// 	(void)w_pos;
// 	t_vect p_pos_c;

// 	p_pos_c = g_cube.curr_map.p_pos;
// 	((unsigned int *)g_cube.img_raycast.buffer)[(int)(w_pos.y * (float)g_cube.curr_map.textures.n_wall.img_height) * (g_cube.img_raycast.sl / 4) + (int)(w_pos.x * (float)g_cube.curr_map.textures.n_wall.img_width)] = 0x00ff0000;
// 	if (!print_ray)
// 		return ;
// 	int i;
// 	i = 0;
// 	while (i < 1000)
// 	{
// 		p_pos_c.x += ray.x/100;
// 		p_pos_c.y += ray.y/100;
// 		if (p_pos_c.x >=0 && p_pos_c.x <= 9 && p_pos_c.y >= 0 && p_pos_c.y <= 9)
// 			((unsigned int *)g_cube.img_raycast.buffer)[(int)(p_pos_c.y * (float)g_cube.curr_map.textures.n_wall.img_height) * (g_cube.img_raycast.sl / 4) + (int)(p_pos_c.x * (float)g_cube.curr_map.textures.n_wall.img_width)] = 0x000000c6;
// 		i++;
// 	}
// }


void	raycast(t_mlx_img new_i)
{
	t_vect	hit;
	t_vect	cam;
	t_vect	ray;
	int		wall_id;
	// int		obj_id[30];
	// t_vect	obj_hit[30];
	int		i;

	set_cam_vect(&cam);
	i = 0;
	while (i < new_i.img_width)
	{
		hit.x = 0.f;
		hit.y = 0.f;
		ray.x = g_cube.curr_map.p_dir.x + (i - new_i.img_width / 2) * cam.x;
		ray.y = g_cube.curr_map.p_dir.y + (i - new_i.img_width / 2) * cam.y;
		wall_id = throw_ray_x(&hit, ray);
		wall_id = throw_ray_y(&hit, ray, wall_id);
		put_coloumn_wall(&ray, hit, wall_id, i);
		// hit.x = 0.f;
		// hit.y = 0.f;
		// obj_id = throw_ray_obj(&hit, ray);
		// put_coloumn_obj(&ray, hit, obj_id, i);
		i++;
	}
}