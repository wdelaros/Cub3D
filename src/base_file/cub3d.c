#include "../../include/cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	if (argc != 2 || ft_isfile(argv[1]) != 5)
		return (ft_dprintf(2, "too many argument or wrong file extension\n") \
		, 1);
	ft_parsing(argv[1], &data);
	data.mlx = mlx_init(1920, 1080, "papelipoupi", false);
	if (!data.mlx)
		exit(EXIT_FAILURE);
	data.mlx = init_image(&data);
	mlx_loop(data.mlx);
	free_image(&data);
	mlx_terminate(data.mlx);
	return (0);
}

	// for (int i = 0; data.wall && data.wall[i]; i++)
	// {
	// 	ft_printf("data.wall[%d]	:", i);
	// 	for (int j = 0; i < data.wall[i][j]; j++)
	// 	{
	// 		if (data.wall[i][j] == GS)
	// 			ft_printf("=");
	// 		else
	// 			ft_printf("%c", data.wall[i][j]);
	// 	}
	// 	ft_printf("\n");
	// }
