#include "cub3D.h"

void	collect_object(t_obj *obj_ptr)
{
	t_obj *ptr;

	ptr = g_cube.curr_map.obj;
	if (ptr->id == obj_ptr->id)
	{
		g_cube.curr_map.obj = ptr->next;
		delete_obj(ptr);
		return ;
	}
	while (ptr->next->id != obj_ptr->id)
		ptr = ptr->next;
	ptr->next = ptr->next->next;
	delete_obj(obj_ptr);
	g_cube.curr_map.collected++;
	return ;
}