#include "../../include/parsing.h"

void	free_image(t_data *data)
{
	if (data->north.img)
		mlx_delete_image(data->mlx, data->north.img);
	if (data->south.img)
		mlx_delete_image(data->mlx, data->south.img);
	if (data->east.img)
		mlx_delete_image(data->mlx, data->east.img);
	if (data->west.img)
		mlx_delete_image(data->mlx, data->west.img);
	ft_free_null(data->wall);
	ft_free_null((char **)data->map);
	ft_xfree(data->north.path);
	ft_xfree(data->south.path);
	ft_xfree(data->east.path);
	ft_xfree(data->west.path);
}

static mlx_image_t	*get_mlx_img(t_data *data, char *path)
{
	mlx_texture_t	texture;
	mlx_image_t		*img;
	xpm_t			*xpm;

	xpm = mlx_load_xpm42(path);
	if (!xpm)
	{
		free_image(data);
		ft_dprintf(2, "Error\nWrong texture\n");
		mlx_terminate(data->mlx);
		exit (1);
	}
	texture = xpm->texture;
	img = mlx_texture_to_image(data->mlx, &texture);
	mlx_delete_texture(&texture);
	return (img);
}

mlx_t	*init_image(t_data *data)
{
	while (!data->north.img || !data->south.img || !data->east.img \
	|| !data->west.img)
	{
		if (!data->north.img)
			data->north.img = get_mlx_img(data, data->north.path);
		else if (!data->south.img)
			data->south.img = get_mlx_img(data, data->south.path);
		else if (!data->east.img)
			data->east.img = get_mlx_img(data, data->east.path);
		else if (!data->west.img)
			data->west.img = get_mlx_img(data, data->west.path);
		else
			break ;
	}
	return (data->mlx);
}
