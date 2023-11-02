#include "../../include/cub3d.h"

int	main(int argc, char *argv[])
{
	if (argc != 2 || ft_isfile(argv[1]) != 5)
		return (ft_dprintf(2, "too many argument or wrong file extension\n") \
		, 1);
	ft_parsing(argv[1]);
	return (0);
}
