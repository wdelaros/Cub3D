#include "../include/raycast.h"

mlx_image_t	*g_img;

void	ft_raycast(t_data *game)
{
}

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*game;

	game = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE || keydata.key == MLX_KEY_Q)
			ft_error_interrupt(game);
		else if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
			ft_putendl_fd("move up", TERM_OUTPUT);
		else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
			ft_putendl_fd("move down", TERM_OUTPUT);
		else if (keydata.key == MLX_KEY_A)
			ft_putendl_fd("move left", TERM_OUTPUT);
		else if (keydata.key == MLX_KEY_D)
			ft_putendl_fd("move right", TERM_OUTPUT);
		else if (keydata.key == MLX_KEY_LEFT)
			ft_putendl_fd("camera left", TERM_OUTPUT);
		else if (keydata.key == MLX_KEY_RIGHT)
			ft_putendl_fd("camera right", TERM_OUTPUT);
	}
	ft_raycast(game);
}

int	main(void)
{
	mlx_t	*mlx;
	t_data	game;

	ft_bzero(&game, sizeof(game));
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, 128, 128);
	ft_memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_key_hook(mlx, ft_hook, &game);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
