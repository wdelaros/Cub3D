#include "../../include/cub3d.h"

void	finalize_map(t_data *data)
{
	int	x = 0;
	int y = 0;

	while (data->wall[x])
		x++;
	data->map = ft_calloc(x + 1, sizeof(int *));
	x = 0;
	while (data->wall[x])
	{
		y = 0;
		while (data->wall[x][y])
		{
			y++;
		}
		data->map[x] = ft_calloc(y + 1, sizeof(int));
		x++;
	}
	x = 0;
	while (data->wall[x])
	{
		y = 0;
		while (data->wall[x][y])
		{
			if (data->wall[x][y] == 'N' || data->wall[x][y] == 'S' || data->wall[x][y] == 'E' || data->wall[x][y] == 'W')
			{
				data->info->pos.x = x + 0.1;
				data->info->pos.y = y + 0.1;
			}
			if (data->wall[x][y] == 'N')
			{
				data->info->dir.x = 1;
				data->info->dir.y = 0;
				data->info->plane.x = 0;
				data->info->plane.y = -0.85;
			}
			if (data->wall[x][y] == 'S')
			{
				data->info->dir.x = 1;
				data->info->dir.y = 0;
				data->info->plane.x = 0;
				data->info->plane.y = -0.85;
			}
			if (data->wall[x][y] == 'E')
			{
				data->info->dir.x = 1;
				data->info->dir.y = 0;
				data->info->plane.x = 0;
				data->info->plane.y = -0.85;
			}
			if (data->wall[x][y] == 'W')
			{
				data->info->dir.x = 1;
				data->info->dir.y = 0;
				data->info->plane.x = 0;
				data->info->plane.y = -0.85;
			}
			if (ft_isdigit(data->wall[x][y]))
				data->map[x][y] = data->wall[x][y] - 48;
			else
				data->map[x][y] = data->wall[x][y] = 0;
			y++;
		}
		x++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_info	info;

	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&info, sizeof(t_info));
	data.info = &info;
	if (argc != 2 || ft_isfile(argv[1]) != 5)
		return (ft_dprintf(2, "too many argument or wrong file extension\n") \
		, 1);
	ft_parsing(argv[1], &data);
	data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "DINDE POMME BACON FROMAGE SUISSE", 0);
	finalize_map(&data);
	// data.mlx = init_image(&data);
	ft_init(&data);
	data.info->color = ft_rgba_to_uint(210.0, 93.0, 0.0);
	ft_raycast(&data);
	mlx_key_hook(data.mlx, ft_hook, &data);
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
