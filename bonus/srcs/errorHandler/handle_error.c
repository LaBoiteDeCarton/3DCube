#include <unistd.h>
#include <stdio.h>
#include "libft.h"

int	handle_file_errors(char *message)
{
	ft_putstr_fd("cub3D: ", STDOUT_FILENO);
	ft_putendl_fd(message, STDOUT_FILENO);
	return (0);
}

void	handle_errors(char *message)
{
	ft_putstr_fd("cub3D: ", STDOUT_FILENO);
	ft_putstr_fd(message, STDOUT_FILENO);
	perror(NULL);
}
