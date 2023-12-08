#include "../../include/raycast.h"

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

void	ft_putnbrendl_fd(int nbr, int fd)
{
	ft_putnbr_fd(nbr, fd);
	ft_putendl_fd("", fd);
}

int	**ft_xpm_convert(xpm_t *xpm)
{
	int	**conv;
	int	x;
	int	y;

	conv = ft_calloc(xpm->texture.height + 1, sizeof(int *));
	y = BASE - 1;
	while (++y < (int)(xpm->texture.height + BASE))
	{
		x = BASE - 1;
		conv[y - BASE] = ft_calloc(xpm->texture.width, sizeof(int));
		while (++x < (int)(xpm->texture.width + BASE))
		{
			conv[y - BASE][x - BASE] = ft_rgba_to_uint(
					xpm->texture.pixels[(xpm->texture.width * BASE \
						* (y - BASE)) + (BASE * (x - BASE))],
					xpm->texture.pixels[(xpm->texture.width * BASE \
						* (y - BASE)) + (BASE * (x - BASE)) + 1],
					xpm->texture.pixels[(xpm->texture.width * BASE \
						* (y - BASE)) + (BASE * (x - BASE)) + 2]
					/*xpm->texture.pixels[(xpm->texture.width * BASE \
						* (y - BASE)) + (BASE * (x - BASE)) + 3]*/);
		}
	}
	return (conv);
}

//find_hit_texture
void	ft_calculate_wall_x(xpm_t *wall, t_data *data)
{
	double	hit;

	hit = 0;
	if (data->info->side == 0 || data->info->side == 2)
		hit = data->info->pos.y + data->info->wall_dist * data->info->ray_dir.y;
	else
		hit = data->info->pos.x + data->info->wall_dist * data->info->ray_dir.x;
	hit -= (int)hit;
	data->info->wall_x = (int)(hit * (double)wall->texture.width);
	if (data->info->side % 2 == 0 && data->info->ray_dir.x > 0)
		data->info->wall_x = wall->texture.width - data->info->wall_x - 1;
	if (data->info->side % 2 == 1 && data->info->ray_dir.y < 0)
		data->info->wall_x = wall->texture.width - data->info->wall_x - 1;
}

//pick_texture
void	ft_draw_texture(int x, t_data *data)
{
	t_sprite	sprite;

	if (data->info->side == 0)
		sprite = data->south;
	else if (data->info->side == 2)
		sprite = data->north;
	else if (data->info->side == 1)
		sprite = data->east;
	else if (data->info->side == 3)
		sprite = data->west;
	ft_calculate_wall_x(sprite.img, data);
	ft_draw_vertical(x, data, sprite.img, sprite.pxl);
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
	while (data->info->hit == 0)
	{
		if (data->info->sd.x < data->info->sd.y)
		{
			data->info->sd.x += data->info->delta_dist.x;
			data->info->map.x += data->info->step.x;
			if (data->info->ray_dir.x > 0)
				data->info->side = 0;
			else
				data->info->side = 2;
		}
		else
		{
			data->info->sd.y += data->info->delta_dist.y;
			data->info->map.y += data->info->step.y;
			if (data->info->ray_dir.y > 0)
				data->info->side = 1;
			else
				data->info->side = 3;
		}
		if (data->map[data->info->map.x][data->info->map.y] > 0)
			data->info->hit = 1;
	}
}

//calum_dist
void	ft_draw_limits(t_info *info)
{
	if (info->side % 2 == 0)
		info->wall_dist = (info->sd.x - info->delta_dist.x);
	else
		info->wall_dist = (info->sd.y - info->delta_dist.y);
	info->line_h = (int)(SCREEN_HEIGHT / info->wall_dist)
	info->draw_start = -(info->line_h) / 2 + SCREEN_HEIGHT / 2;
	info->draw_end = info->line_h / 2 + SCREEN_HEIGHT / 2;
	if (info->draw_start < 0)
		info->draw_start = 0;
	if (info->draw_end >= SCREEN_HEIGHT)
		info->draw_end = SCREEN_HEIGHT - 1;
}

//init_raycast
void	ft_raycast_calcs(int x, t_info *info)
{
	info->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	info->ray_dir.x = info->dir.x + info->plane.x * info->camera_x;
	info->ray_dir.y = info->dir.y + info->plane.y * info->camera_x;
	info->map.x = (int)info->pos.x;
	info->map.y = (int)info->pos.y;
	info->delta_dist.x = fabs(1 / info->ray_dir.x);
	info->delta_dist.y = fabs(1 / info->ray_dir.y);
	info->hit = 0;
	info->side = 0;
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

void	ft_move_up(t_info *info, int **map2)
{
	double	moved_x;
	double	moved_y;

	moved_x = info->pos.x + info->dir.x * info->speed.move;
	moved_y = info->pos.y + info->dir.y * info->speed.move;
	if (map2[(int)(moved_x + info->dir.x * HITBOX)][(int)info->pos.y] == false)
		info->pos.x = moved_x;
	if (map2[(int)info->pos.x][(int)(moved_y + info->dir.y * HITBOX)] == false)
		info->pos.y = moved_y;
}

void	ft_move_down(t_info *info, int **map2)
{
	double	moved_x;
	double	moved_y;

	moved_x = info->pos.x - info->dir.x * info->speed.move;
	moved_y = info->pos.y - info->dir.y * info->speed.move;
	if (map2[(int)(moved_x + info->dir.x * -HITBOX)][(int)info->pos.y] == false)
		info->pos.x = moved_x;
	if (map2[(int)info->pos.x][(int)(moved_y + info->dir.y * -HITBOX)] == false)
		info->pos.y = moved_y;
}

void ft_move_left(t_info *info, int **map2)
{
	double	moved_x;
	double	moved_y;

	moved_x = info->pos.x - info->dir.y * info->speed.move;
	moved_y = info->pos.y + info->dir.x * info->speed.move;
	if (map2[(int)(moved_x + info->dir.y * HITBOX)][(int)info->pos.y] == false)
		info->pos.x = moved_x;
	if (map2[(int)info->pos.x][(int)(moved_y + info->dir.x * HITBOX)] == false)
		info->pos.y = moved_y;
}

void ft_move_right(t_info *info, int **map2)
{
	double	moved_x;
	double	moved_y;

	moved_x = info->pos.x + info->dir.y * info->speed.move;
	moved_y = info->pos.y - info->dir.x * info->speed.move;
	if (map2[(int)(moved_x + info->dir.y * -HITBOX)][(int)info->pos.y] == false)
		info->pos.x = moved_x;
	if (map2[(int)info->pos.x][(int)(moved_y + info->dir.x * -HITBOX)] == false)
		info->pos.y = moved_y;
}

void	ft_hero_move(t_data *data, char move)
{
	if (move == UP)
		ft_move_up(data->info, data->map);
	else if (move == DOWN)
		ft_move_down(data->info, data->map);
	else if (move == LEFT)
		ft_move_left(data->info, data->map);
	else if (move == RIGHT)
		ft_move_right(data->info, data->map);
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
}

void	ft_camera_move(t_data *data, char move)
{
	if (move == RIGHT)
		ft_camera_right(data->info);
	else if (move == LEFT)
		ft_camera_left(data->info);
}

//draw_wall || draw_vert_pix
void	ft_draw_vertical(int x, t_data *data, xpm_t *wall, int **pxl)
{
	int	y;
	int	wall_y;

	y = data->info->draw_start;
	data->info->dist = 1.0 * wall->texture.height / data->info->line_h;
	data->info->pa = ((double)data->info->draw_start - (double)SCREEN_HEIGHT \
			* 0.5 + (double)data->info->line_h * 0.5) * data->info->dist;
	if (data->info->pa < 0)
		data->info->pa = 0;
	while (y < data->info->draw_end)
	{
		wall_y = (int)data->info->pa;
		if (data->info->pa > wall->texture.height - 1)
			data->info->pa = wall->texture.height - 1;
		data->info->pa += data->info->dist;
		//mlx_put_pixel(data->raycast, x, y, data->info->color);
		mlx_put_pixel(data->raycast, x, y, pxl[wall_y][data->info->wall_x]);
		y++;
	}
}

void	ft_raycast(t_data *data)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ft_raycast_calcs(x, data->info);
		ft_step_direction(data->info);
		ft_dda(data);
		ft_wall_distance(data->info);
		ft_draw_limits(data->info);
		ft_draw_texture(x, data);
		//ft_draw_vertical(x, data);
		x++;
	}
}

void	ft_hook(mlx_key_data_t keydata, void *param)
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
		else if (keydata.key == MLX_KEY_A)
			ft_hero_move(data, LEFT);
	else if (keydata.key == MLX_KEY_D)
			ft_hero_move(data, RIGHT);
		else if (keydata.key == MLX_KEY_LEFT)
			ft_camera_move(data, LEFT);
		else if (keydata.key == MLX_KEY_RIGHT)
			ft_camera_move(data, RIGHT);
	}
	ft_bzero(data->raycast->pixels, (SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(int)));
	ft_raycast(data);
}

void	ft_sky()
{	
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(data->back, x, y, \
					ft_rgba_to_uint(data->c_sky.r, 
							data->c_sky.g, 
							data->c_sky.b));
			x++;
		}
		y++;
	}
}

void	ft_sky_and_floor(t_data *data)
{
	int	x;
	int	y;

	y = 0;

	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(data->back, x, y, \
					ft_rgba_to_uint(data->c_floor.r, data->c_floor.g, data->c_floor.b));
			x++;
		}
		y++;
	}
}

void	ft_init(t_data *data)
{
	data->back = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->raycast = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->info->speed.move =  0.5;
	data->info->speed.rota = 0.3;
	ft_sky_and_floor(data);
	mlx_image_to_window(data->mlx, data->back, 0, 0);
	mlx_image_to_window(data->mlx, data->raycast, 0, 0);
	data->north.pxl = ft_xpm_convert(data->north.img);
	data->south.pxl = ft_xpm_convert(data->south.img);
	data->east.pxl = ft_xpm_convert(data->east.img);
	data->west.pxl = ft_xpm_convert(data->west.img);
	data->info->color = ft_rgba_to_uint(210.0, 93.0, 0.0);
	//data->info->color = ft_rgba_to_uint(0.0, 231.0, 231.0);
}
