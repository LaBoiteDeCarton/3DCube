#include "cub3D.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#define _USE_MATH_DEFINES

void	set_cam_vect(t_vect *vect)
{
	vect->x = -g_cube.curr_map.p_dir.y;
	vect->y = g_cube.curr_map.p_dir.x;
	vect->x = (vect->x * 2) / (3 * g_cube.img_raycast.img_width / 2);
	vect->y = (vect->y * 2) / (3 * g_cube.img_raycast.img_width / 2);
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
	i = -1;
	while (++i < (g_cube.img_raycast.img_height / 2) - (wall_size / 2))
			((unsigned int *)g_cube.img_raycast.buffer)[i * (g_cube.img_raycast.sl / 4) + coloumn] = g_cube.curr_map.cell_color;
	while (i < (g_cube.img_raycast.img_height / 2) + (wall_size / 2))
	{
		wall_line = (int)((float)(i - ((g_cube.img_raycast.img_height / 2) - (wall_size / 2))) * (float)mlx_img.img_height / (float)wall_size);
		if (i < g_cube.img_raycast.img_height && i > 0 && wall_coloumn < mlx_img.img_width && wall_line < mlx_img.img_height)
		{
			if (((unsigned int *)(mlx_img.buffer))[wall_line  * (mlx_img.sl / 4) + wall_coloumn] == 0x001a3b72)
				((unsigned int *)g_cube.img_raycast.buffer)[i * (g_cube.img_raycast.sl / 4) + coloumn] += 0x00050510;
			else if (((unsigned int *)(mlx_img.buffer))[wall_line  * (mlx_img.sl / 4) + wall_coloumn] != 0x00000000)
				((unsigned int *)g_cube.img_raycast.buffer)[i * (g_cube.img_raycast.sl / 4) + coloumn] = 
					((unsigned int *)(mlx_img.buffer))[wall_line  * (mlx_img.sl / 4) + wall_coloumn];
		}
		i++;
	}
	while (i < g_cube.img_raycast.img_height)
		((unsigned int *)g_cube.img_raycast.buffer)[i++ * (g_cube.img_raycast.sl / 4) + coloumn] = g_cube.curr_map.floor_color;
}
#include <stdio.h>

void	put_coloumn_obj(t_vect *ray, t_vect pos, int obj_id, int coloumn)
{
	float	fraction;
	float	real_x;
	float	real_y;
	int		i;
	int		wall_coloumn;
	int		wall_line;
	int		obj_size;
	t_obj	*obj_ptr;
	t_mlx_img	mlx_img;

	obj_ptr = g_cube.curr_map.obj;
	while (obj_ptr && obj_ptr->id != obj_id)
		obj_ptr = obj_ptr->next;
	if (obj_ptr == NULL)
		return ;
	mlx_img = obj_ptr->txtr;
	real_x = pos.x - g_cube.curr_map.p_pos.x;
	real_y = pos.y - g_cube.curr_map.p_pos.y;
	fraction = sqrtf((real_x * real_x + real_y * real_y) / (ray->x * ray->x + ray->y * ray->y));
	obj_size = (int)(obj_ptr->size * (float)g_cube.img_raycast.img_width / (2.5 * fraction * tan(M_PI / 6)));
	i = (g_cube.img_raycast.img_height / 2) - (obj_size / 2);
	if (obj_ptr->type == v_wall || obj_ptr->type == v_door)
		wall_coloumn = (obj_ptr->pos.y - pos.y + 0.5) * mlx_img.img_width;
	else if (obj_ptr->type == h_wall || obj_ptr->type == h_door)
		wall_coloumn = (obj_ptr->pos.x - pos.x + 0.5) * mlx_img.img_width;
	else if ((obj_ptr->pos.x - g_cube.curr_map.p_pos.x) * (pos.y - g_cube.curr_map.p_pos.y)
		< (obj_ptr->pos.y - g_cube.curr_map.p_pos.y) * (pos.x - g_cube.curr_map.p_pos.x))
		wall_coloumn = (0.5 + sqrtf((obj_ptr->pos.x - pos.x) * (obj_ptr->pos.x - pos.x) + (obj_ptr->pos.y - pos.y) * (obj_ptr->pos.y - pos.y))) * mlx_img.img_width;
	else
		wall_coloumn = (0.5 - sqrtf((obj_ptr->pos.x - pos.x) * (obj_ptr->pos.x - pos.x) + (obj_ptr->pos.y - pos.y) * (obj_ptr->pos.y - pos.y))) * mlx_img.img_width;
	while (i < (g_cube.img_raycast.img_height / 2) + (obj_size / 2))
	{
		wall_line = (int)((float)(i - ((g_cube.img_raycast.img_height / 2) - (obj_size / 2))) * (float)mlx_img.img_height / (float)obj_size);
		if (i < g_cube.img_raycast.img_height && i > 0 && wall_coloumn < mlx_img.img_width && wall_line < mlx_img.img_height)
		{
			if (((unsigned int *)(mlx_img.buffer))[wall_line  * (mlx_img.sl / 4) + wall_coloumn] == 0x001a3b72)
				((unsigned int *)g_cube.img_raycast.buffer)[i * (g_cube.img_raycast.sl / 4) + coloumn] += 0x00050510;
			else if (((unsigned int *)(mlx_img.buffer))[wall_line  * (mlx_img.sl / 4) + wall_coloumn] != 0x00000000)
				((unsigned int *)g_cube.img_raycast.buffer)[i * (g_cube.img_raycast.sl / 4) + coloumn] = 
					((unsigned int *)(mlx_img.buffer))[wall_line  * (mlx_img.sl / 4) + wall_coloumn];
		}
		i++;
	}
}

void	put_coloumn_objs(t_vect *ray, t_vect hit, t_obj_hit *all, int i)
{
	//ici on doit trier d'abord
	while (all)
	{
		if ((g_cube.curr_map.p_pos.x < hit.x && all->hit_pos.x < hit.x && all->hit_pos.x > g_cube.curr_map.p_pos.x)
			|| (g_cube.curr_map.p_pos.x > hit.x && all->hit_pos.x > hit.x && all->hit_pos.x < g_cube.curr_map.p_pos.x))
			put_coloumn_obj(ray, all->hit_pos, all->obj_id, i);
		all = all->next;
	}
}

static t_obj_hit *throw_ray_v_obj(t_obj *obj, t_obj_hit *old, t_vect ray)
{
	float	x;
	float	y;
	float	m;
	t_obj_hit	*new;

	m = ray.y / ray.x;
	x = obj->pos.x;
	y = m * (x - g_cube.curr_map.p_pos.x) + g_cube.curr_map.p_pos.y;
	if (y >= obj->pos.y - 0.5 && y <= obj->pos.y + 0.5)
	{
		new = malloc(sizeof(t_obj_hit));
		if (!new)
		{
			handle_errors("hit object info is lost");
			return (old);
		}
		new->next = old;
		new->obj_id = obj->id;
		new->hit_pos.x = x;
		new->hit_pos.y = y;
		return (new);
	}
	else
		return (old);
}

static t_obj_hit *throw_ray_h_obj(t_obj *obj, t_obj_hit *old, t_vect ray)
{
	float	x;
	float	y;
	float	m;
	t_obj_hit	*new;

	m = ray.x / ray.y;
	y = obj->pos.y;
	x = m * (y - g_cube.curr_map.p_pos.y) + g_cube.curr_map.p_pos.x;
	if (x >= obj->pos.x - 0.5 && x <= obj->pos.x + 0.5)
	{
		new = malloc(sizeof(t_obj_hit));
		if (!new)
		{
			handle_errors("hit object info is lost");
			return (old);
		}
		new->next = old;
		new->obj_id = obj->id;
		new->hit_pos.x = x;
		new->hit_pos.y = y;
		return (new);
	}
	else
		return (old);
}

static t_obj_hit *throw_ray_normal_obj(t_obj *obj, t_obj_hit *old, t_vect ray)
{
	float alpha;
	t_vect obj_dir;
	float x;
	float y;
	t_obj_hit	*new;

	obj_dir.x = obj->pos.x - g_cube.curr_map.p_pos.x;
	obj_dir.y = obj->pos.y - g_cube.curr_map.p_pos.y;
	alpha = (obj_dir.x * obj_dir.x + obj_dir.y * obj_dir.y)
		/ (obj_dir.x * ray.x + obj_dir.y * ray.y);
	x = g_cube.curr_map.p_pos.x + alpha * ray.x;
	y = g_cube.curr_map.p_pos.y + alpha * ray.y;
	if ((obj->pos.x - x) * (obj->pos.x - x) + (obj->pos.y - y) * (obj->pos.y - y) <= (obj->size / 2) * (obj->size / 2))
	{
		new = malloc(sizeof(t_obj_hit));
		if (!new)
		{
			handle_errors("hit object info is lost");
			return (old);
		}
		new->next = old;
		new->obj_id = obj->id;
		new->hit_pos.x = x;
		new->hit_pos.y = y;
		return (new);
	}
	return (old);
}

t_obj_hit	*throw_ray_obj(t_vect ray)
{
	t_obj		*obj_ptr;
	t_obj_hit	*all_hit_obj;

	obj_ptr = g_cube.curr_map.obj;
	all_hit_obj = NULL;
	while (obj_ptr)
	{
		if (obj_ptr->type == v_wall || obj_ptr->type == v_door)
			all_hit_obj = throw_ray_v_obj(obj_ptr, all_hit_obj, ray);
		else if (obj_ptr->type == h_wall || obj_ptr->type == h_door)
			all_hit_obj = throw_ray_h_obj(obj_ptr, all_hit_obj, ray);
		else
			all_hit_obj = throw_ray_normal_obj(obj_ptr, all_hit_obj, ray);
		obj_ptr = obj_ptr->next;
	}
	return (all_hit_obj);
}

void freeeee(t_obj_hit *obj_hit)
{
	if (obj_hit)
	{
		freeeee(obj_hit->next);
		free(obj_hit);
	}
}

void	raycast(t_mlx_img new_i)
{
	t_vect	hit;
	t_vect	cam;
	t_vect	ray;
	int		wall_id;
	t_obj_hit	*obj_hit;
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
		obj_hit = throw_ray_obj(ray);
		put_coloumn_objs(&ray, hit, obj_hit, i);

		//leaks correction a modifier
		freeeee(obj_hit);
		i++;
	}
}