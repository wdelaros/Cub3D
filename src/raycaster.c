#include "../include/raycast.h"

int map[8][8]=
{
{1,1,1,1,1,1,1,1},
{1,0,1,0,0,0,0,1},
{1,0,1,0,0,0,0,1},
{1,0,1,0,0,0,0,1},
{1,0,0,0,0,0,0,1},
{1,0,0,0,0,1,0,1},
{1,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1},	
};

uint32_t	ft_rgba_to_uint(double r, double g, double b)
{
	return ((r * 16777216) + (g * 65536) + (b * 256) + 0xFF);
}

double	ft_deg_to_rad(int angle)
{
	return (angle * M_PI / 180.0);
}

//cal_side_dist_x & cal_side_dist_y
void	ft_step_direction(t_info *info)
{
	if (info->ray_dir.x < 0)
	{
		info->step.x = -1;
		info->sd.x = (info->pos.x - info->map.x) * info->delta_dist.x;
	}
	else
	{
		info->step.x = 1;
		info->sd.x = (info->map.x + 1.0 - info->pos.x) * info->delta_dist.x;
	}
	if (info->ray_dir.y < 0)
	{
		info->step.y = -1;
		info->sd.y = (info->pos.y - info->map.y) * info->delta_dist.y;
	}
	else
	{
		info->step.y = 1;
		info->sd.y = (info->map.y + 1.0 - info->pos.y) * info->delta_dist.y;
	}
}

//dda
void	ft_dda(t_data *data)
{
	t_info	*info;

	info = data->info;
	while (info->hit == 0)
	{
		if (info->sd.x < info->sd.y)
		{
			info->sd.x += info->delta_dist.x;
			info->map.x += info->step.x;
			info->side = 0;
		}
		else
		{
			info->sd.y += info->delta_dist.y;
			info->map.y += info->step.y;
			info->side = 1;
		}
		if (map[info->map.x][info->map.y] > 0)
			info->hit = 1;
	}
}

//calum_dist
void	ft_draw_limits(t_info *info)
{
	info->draw_start = -(info->line_h) / 2 + SCREEN_HEIGHT / 2;
	info->draw_end = info->line_h / 2 + SCREEN_HEIGHT / 2;
	if (info->draw_start < 0)
		info->draw_start = 0;
	if (info->draw_end >= SCREEN_HEIGHT)
		info->draw_end = SCREEN_HEIGHT - 1;
}

//
void	ft_raycast_calcs(t_info *info)
{
	info->ray_dir.x = info->dir.x + info->plane.x * info->camera_x;
	info->ray_dir.y = info->dir.y + info->plane.y * info->camera_x;
	info->map.x = (int)info->pos.x;
	info->map.y = (int)info->pos.y;
	info->delta_dist.x = fabs(1 / info->ray_dir.x);
	info->delta_dist.y = fabs(1 / info->ray_dir.y);
}

//wall_height
void	ft_wall_distance(t_info *info)
{
	if (info->side == 0)
		info->wall_dist = (info->sd.x - info->delta_dist.x);
	else
		info->wall_dist = (info->sd.y - info->delta_dist.y);
	info->line_h = (int)SCREEN_HEIGHT / info->wall_dist;
}

void	ft_hero_move(t_data *data, char move)
{
	int	moved_x;
	int	moved_y;
	t_info	*info;

	info = data->info;
	if (move == UP)
	{
		moved_x = info->pos.x + info->dir.x * info->speed.move;
		moved_y = info->pos.y + info->dir.y * info->speed.move;
		if (map[(int)moved_x][(int)info->pos.y] == false)
			info->pos.x += info->dir.x * info->speed.move;
		if (map[(int)info->pos.x][(int)moved_y] == false)
			info->pos.y += info->dir.y * info->speed.move;
		data->info->color = ft_rgba_to_uint(0.0, 210.0, 210.0);
		ft_putendl_fd("up", ERROR_OUTPUT);
	}
	if (move == DOWN)
	{
		moved_x = info->pos.x - info->dir.x * info->speed.move;
		moved_y = info->pos.y - info->dir.y * info->speed.move;
		if (map[(int)moved_x][(int)info->pos.y] == false)
			info->pos.x -= info->dir.x * info->speed.move;
		if (map[(int)info->pos.x][(int)moved_y] == false)
			info->pos.y -= info->dir.y * info->speed.move;
		data->info->color = ft_rgba_to_uint(210.0, 93.0, 0.0);
		ft_putendl_fd("down", ERROR_OUTPUT);
	}
}

void	ft_camera_right(t_info *in)
{
	double old_plane;
	double old_dir;

	old_dir = in->dir.x;
	in->dir.x = in->dir.x * cos(-in->speed.rota) - \
			in->dir.y * sin(-in->speed.rota);
	in->dir.y = old_dir * sin(-in->speed.rota) + \
			in->dir.y * cos(-in->speed.rota);
	old_plane = in->plane.x;
	in->plane.x = in->plane.x * cos(-in->speed.rota) - \
			in->plane.y * sin(-in->speed.rota);
	in->plane.y = old_plane * sin(-in->speed.rota) + \
			in->plane.y * cos(-in->speed.rota);
	in->color = ft_rgba_to_uint(222.0, 30.0, 210.0);
	ft_putendl_fd("right", ERROR_OUTPUT);
}

void	ft_camera_left(t_info *in)
{
	double old_plane;
	double old_dir;

	old_dir = in->dir.x;
	in->dir.x = in->dir.x * cos(in->speed.rota) - \
			in->dir.y * sin(in->speed.rota);
	in->dir.y = old_dir * sin(in->speed.rota) + \
			in->dir.y * cos(in->speed.rota);
	old_plane = in->plane.x;
	in->plane.x = in->plane.x * cos(in->speed.rota) - \
			in->plane.y * sin(in->speed.rota);
	in->plane.y = old_plane * sin(in->speed.rota) + \
			in->plane.y * cos(in->speed.rota);
	in->color = ft_rgba_to_uint(222.0, 0.0, 0.0);
	ft_putendl_fd("left", ERROR_OUTPUT);
}

void	ft_camera_move(t_data *data, char move)
{
	if (move == RIGHT)
		ft_camera_right(data->info);
	else if (move == LEFT)
		ft_camera_left(data->info);
}

void	ft_draw_vertical(int x, t_data *data)
{
	int	y;

	y = data->info->draw_start;
	while (y < data->info->draw_end)
	{
		mlx_put_pixel(data->raycast, x, y, ft_rgba_to_uint(221.0, 93.0, 0.0));
		y++;
	}
	/*int w = SCREEN_WIDTH / 4;
	int h = SCREEN_HEIGHT /4;
	y = h;
	while (y < h * 3)
	{
		x = w;
		while (x < w * 3)
		{
			mlx_put_pixel(data->raycast, x, y, data->info->color);
			x++;
		}
		y++;
	}*/
}

void	ft_raycast(t_data *data)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		data->info->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		ft_step_direction(data->info);
		ft_raycast_calcs(data->info);
		ft_dda(data);
		ft_wall_distance(data->info);
		ft_draw_limits(data->info);
		//ft_set_texture(data);
		ft_draw_vertical(x, data);
		x++;
	}
}

void	ft_verif_vert_line(int x, t_info *info)
{
	if (info->draw_end < info->draw_start)
	{
		info->draw_start += info->draw_end;
		info->draw_end = info->draw_start - info->draw_end;
		info->draw_start -= info->draw_end;
	}
	if (info->draw_end < 0 || info->draw_start >= SCREEN_HEIGHT \
		|| x < 0 || x >= SCREEN_WIDTH)
		return ;
	if (info->draw_start < 0)
		info->draw_start = 0;
	if (info->draw_end >= SCREEN_WIDTH)
		info->draw_end = SCREEN_HEIGHT - 1;
}

/*int	ft_vert_line(int x, t_data *data, t_color color)
{
	unsigned int	color_pixel;
	unsigned int*	bufp;
	int				y;

	ft_verif_vert_line(x, data->info);
	color_pixel= ft_rgba_to_uint(color.r, color.g, color.b);
	bufp = (unsigned int*)map + data->info->draw_start * SCREEN_WIDTH + x;
	y = data->info->draw_start;
	while (y <= data->info->draw_end)
	{
		*bufp = color_pixel;
		bufp += (unsigned int)SCREEN_WIDTH;
		y++;
	}
	return 1;
}*/

static void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE || keydata.key == MLX_KEY_Q)
			ft_error_interrupt();
		else if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
			ft_hero_move(data, UP);
		else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
			ft_hero_move(data, DOWN);
		else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
			ft_camera_move(data, LEFT);
		else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
			ft_camera_move(data, RIGHT);
	}
	ft_bzero(data->raycast->pixels, (SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(int)));
	ft_raycast(data);
	//ft_test(data);
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

void	ft_test(t_data *data)
{
	int x;
	int y;
	int w = SCREEN_WIDTH / 4;
	int h = SCREEN_HEIGHT / 4;

	y = h;
	while (y < h * 3)
	{
		x = w;
		while (x < w * 3)
		{
			mlx_put_pixel(data->raycast, x, y, ft_rgba_to_uint(221.0, 93.0, 0.0));
			x++;
		}
		y++;
	}
}

void	ft_init(t_data *data)
{
	data->back = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->raycast = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->info->speed.move = data->mlx->delta_time * 5.0;
	data->info->speed.rota = data->mlx->delta_time * 3.0;
	data->info->pd.x = cos(data->info->pa) * data->info->speed.rota;
	data->info->pd.y = sin(data->info->pa) * data->info->speed.rota;
	ft_sky_and_floor(data);
	//ft_test(data);
	mlx_image_to_window(data->mlx, data->back, 0, 0);
	mlx_image_to_window(data->mlx, data->raycast, 0, 0);
}

int main(void)
{
	t_data	data;
	t_info	info;

	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&info, sizeof(t_info));
	data.info = &info;
	data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "DINDE POMME BACON", 0);
	ft_init(&data);
	mlx_key_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
