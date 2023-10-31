#include "../../include/cub3d.h"

int main(int argc, char *argv[])
{
	if (argc != 2 || ft_isfile(argv[argc - 1]) != 5)
		return (ft_dprintf(2, "wrong extension\n"), 1);
	return (0);
}
