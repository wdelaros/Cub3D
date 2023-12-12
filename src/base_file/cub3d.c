/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:49:28 by wdelaros          #+#    #+#             */
/*   Updated: 2023/12/12 11:49:02 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_direction(t_data *data, double dir, double plane)
{
	if (dir == 1)
		data->info->dir.x = 1;
	else if (dir == 2)
		data->info->dir.y = 1;
	else if (dir == -1)
		data->info->dir.x = -1;
	else if (dir == -2)
		data->info->dir.y = -1;
	if (plane == 1)
		data->info->plane.x = 0.85;
	else if (plane == 2)
		data->info->plane.y = 0.85;
	else if (plane == -1)
		data->info->plane.x = -0.85;
	else if (plane == -2)
		data->info->plane.y = -0.85;
}

static int	set_pos(t_data *data, double x, double y)
{
	data->info->pos.x = x + 0.5;
	data->info->pos.y = y + 0.5;
	return (1);
}

static int	alloc_map(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	data->wall = ft_arrayzero(data->wall, data->wall[0]);
	while (data->wall[x])
	{
		data->wall[x] = ft_ffstrjoin(ft_strdup("1"), data->wall[x]);
		data->wall[x] = ft_fstrjoin(data->wall[x], "1");
		x++;
	}
	data->wall = ft_arrayjoin(data->wall, data->wall[x - 1]);
	data->map = ft_calloc(x + 2, sizeof(int *));
	x = 0;
	while (data->wall[x])
	{
		y = 0;
		while (data->wall[x][y])
			y++;
		data->map[x] = ft_calloc(y + 1, sizeof(int));
		x++;
	}
	return (0);
}

static void	finalize_map(t_data *data)
{
	int	x;
	int	y;

	x = alloc_map(data);
	while (data->wall[x])
	{
		y = 0;
		while (data->wall[x][y])
		{
			if (data->wall[x][y] == 'N' && set_pos(data, x, y))
				set_direction(data, -1, 2);
			if (data->wall[x][y] == 'S' && set_pos(data, x, y))
				set_direction(data, 1, -2);
			if (data->wall[x][y] == 'E' && set_pos(data, x, y))
				set_direction(data, 2, 1);
			if (data->wall[x][y] == 'W' && set_pos(data, x, y))
				set_direction(data, -2, -1);
			if (data->wall[x][y] == GS || data->wall[x][y] == '1')
				data->map[x][y] = 1;
			else
				data->map[x][y] = 0;
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
	data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, \
	"DINDE POMME BACON FROMAGE SUISSE", 0);
	finalize_map(&data);
	data.mlx = init_image(&data);
	ft_init(&data);
	ft_raycast(&data);
	mlx_key_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	free_image(&data);
	mlx_terminate(data.mlx);
	return (0);
}
