#include "../include/error.h"

void	ft_error_interrupt(t_data *game)
{
	(void)game;
	ft_putendl_fd("Interrupted!", ERROR_OUTPUT);
	exit(EXIT_FAILURE);
}
