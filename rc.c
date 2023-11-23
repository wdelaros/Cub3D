#include <stdio.h>
#include <stdlib.h>
#include "include/raycast.h"
#include "include/structure.h"
#include "MLX42/include/MLX42/MLX42.h"

int map[]=
{
 1,1,1,1,1,1,1,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,1,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,	
};

unsigned int	ft_rgba_to_uint(double r, double g, double b)
{
	return ((r * 16777216) + (g * 65536) + (b * 256) + 0xFF);
}

void	ft_sky_and_floor(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(data->back, x, y, ft_rgba_to_uint(120.0, 60.0, 180.0));
			x++;
		}
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(data->back, x, y, ft_rgba_to_uint(210.0, 186.0, 150.0));
			x++;
		}
		y++;
	}
}

void	ft_init(t_data *data)
{
	data->back = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->raycast = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->info->speed.move = mlx->delta_time * 5.0;
	data->info->speed.rota = mlx->delta_time * 3.0;
	info->pd.x = cos(info->pa) * info->speed.rota;
	info->pd.y = sin(info->pa) * info->speed.rota;
	ft_sky_and_floor(data);
	mlx_image_to_window(data->mlx, data->back, 0, 0);
}

void	ft_up(t_info *info)
{
	ft_putendl_fd("up", 2);
	info->pos.x += info->pd.x;
	info->pos.y += info->pd.y;
}

void	ft_down(t_info *info)
{
	ft_putendl_fd("down", 2);
	info->pos.x += info->pd.x;
	info->pos.y += info->pd.y;
}

void	ft_left(t_info *info)
{
	ft_putendl_fd("left", 2);
	info->pa -= 0.1;
	if (info->pa < 0)
		pa += 2 + PI;
	info->pd.x = cos(info->pa) * info->speed.rota;
	info->pd.y = sin(info->pa) * info->speed.rota;
}

void	ft_right(t_info *info)
{
	ft_putendl_fd("right", 2);
	info->pa += 0.1;
	if (info->pa > 2 * PI)
		pa -= 2 * PI;
	info->pd.x = cos(info->pa) * info->speed.rota;
	info->pd.y = sin(info->pa) * info->speed.rota;
}

static void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE || keydata.key == MLX_KEY_Q)
			ft_error_interrupt();
		else if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
			ft_up(data);
		else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
			ft_down(data);
		else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
			ft_left(data);
		else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
			ft_right(data);
	}
}

int main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "DINDE POMME BACON", 0);
	ft_init(&data);
	mlx_key_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
