#include "../../include/raycast.h"

void	ft_init(t_data *data)
{
	data->back = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->raycast = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->info->speed.move = 0.5;
	data->info->speed.rota = 0.3;
	ft_sky_and_floor(data);
	mlx_image_to_window(data->mlx, data->back, 0, 0);
	mlx_image_to_window(data->mlx, data->raycast, 0, 0);
	data->north.pxl = ft_xpm_convert(data->north.img);
	data->south.pxl = ft_xpm_convert(data->south.img);
	data->east.pxl = ft_xpm_convert(data->east.img);
	data->west.pxl = ft_xpm_convert(data->west.img);
}
