#include "../../include/cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	if (argc != 2 || ft_isfile(argv[1]) != 5)
		return (ft_dprintf(2, "too many argument or wrong file extension\n") \
		, 1);
	ft_parsing(argv[1], &data);
	for (int i = 0; data.wall && data.wall[i]; i++)
		ft_printf("data.wall[%d]	:%s\n", i, data.wall[i]);
	ft_printf("\n");
	for (int i = 0; data.floor && data.floor[i]; i++)
		ft_printf("data.floor[%d]	:%s\n", i, data.floor[i]);
	ft_printf("\n");
	for (int i = 0; data.sky && data.sky[i]; i++)
		ft_printf("data.sky[%d]	:%s\n", i, data.sky[i]);
	return (0);
}
