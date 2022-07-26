#include "cub3D.h"

unsigned int	get_time(struct timeval tstart)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return ((tval.tv_sec - tstart.tv_sec) * 1000000
		+ tval.tv_usec - tstart.tv_usec);
}