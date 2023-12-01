#include "../../include/error.h"

void	ft_error_interrupt(void)
{
	ft_putendl_fd("Interrupted!", ERROR_OUTPUT);
	exit(EXIT_FAILURE);
}
