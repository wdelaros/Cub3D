#include "include/raycast.h"

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

double	ft_deg_to_rad(int angle)
{
	return (angle * M_PI / 180.0);
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

int	ft_angle_fix(int angle)
{
	if (angle > 359)
		angle -= 360;
	if (a < 0)
		angle += 360;
	return (angle);
}

void	ft_vert_angle_check(t_info *info)
{
	double	calc_tan;

	calc_tan = tan(degToRad(ra));
	if (cos(degToRad(ra)) > 0.001)
	{
		rx = (((int)px >> 6) << 6) + 64;
		ry = (px-rx) * calc_tan + py;
		xo = 64;
		yo = -xo * calc_tan;
	}
	else if (cos(degToRad(ra)) < -0.001)
	{
		rx = (((int)px >> 6) << 6) - 0.0001;
		ry = (px - rx) * calc_tan + py;
		xo =- 64;
		yo =- xo * calc_tan;
	}
	else
	{
		rx = px;
		ry = py;
		dist_off = 8;
	}
}

void	ft_vert_check(t_info *info)
{
	dof = 0;
	side = 0;
	disV = 100000;
	ft_vert_angle_check(data);
	while (dof<8)
	{
		mx = (int)(rx) >> 6;
		my = (int)(ry) >> 6;
		mp = my * mapX + mx;
		if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
		{
			dof=8;
			disV = cos(degToRad(ra)) * (rx-px) - sin(degToRad(ra)) * (ry-py);
		}
		else
		{
			rx+=xo;
			ry+=yo;
			dof+=1;
		}
  	}
	vx=rx;
	vy=ry;
}

void	ft_horiz_angle_check(t_info *info)
{
	double	calc_tan;

	calc_tan = 1.0 / calc_tan;
	if (sin(degToRad(ra))> 0.001)
	{
		ry = (((int)py >> 6) << 6) - 0.0001;
		rx = (py-ry) * calc_tan + px;
		yo=-64;
		xo =- yo * calc_tan;
	}
	else if(sin(degToRad(ra))<-0.001)
	{
		ry = (((int)py >> 6) << 6) + 64;
		rx = (py-ry) * calc_tan + px;
		yo = 64;
		xo =- yo * calc_tan;
	}
	else
	{
		rx=px;
		ry=py;
		dof=8;
	}
}

void	ft_horiz_check(t_info *info)
{
	dof = 0;
	disH = 100000;
	while (dof < 8)
	{
		mx = (int)(rx) >> 6;
		my = (int)(ry) >> 6;
		mp = my * mapX + mx;
		if(mp > 0 && mp < mapX * mapY && map[mp] == 1)
		{
			dof = 8;
			disH = cos(degToRad(ra)) * (rx-px) - sin(degToRad(ra)) * (ry-py);
		}
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
}


void	ft_dda(t_data *data)
{
	ft_horiz_check(data->info);
	ft_vert_check(data->info);
}


//PUT IN FUNCTION AFTER DRAW
ra=FixAng(ra-1);

void	ft_up(t_info *info)
{
	ft_putendl_fd("up", 2);
	info->pos.x += info->pd.x;
	info->pos.y += info->pd.y;
}

void	ft_down(t_info *info)
{
	ft_putendl_fd("down", 2);
	info->pos.x += info->pd.x * info->speed.move;
	info->pos.y += info->pd.y * info->speed.move;
}

void	ft_left(t_info *info)
{
	ft_putendl_fd("left", 2);
	info->pa -= info->speed.rota;
	info->pa = ft_angle_fix(info->pa);
	info->pd.x = cos(ft_deg_to_rad(info->pa));
	info->pd.y = sin(ft_deg_to_rad(info->pa));
}

void	ft_right(t_info *info)
{
	ft_putendl_fd("right", 2);
	info->pa += info->speed.rota;
	info->pa = ft_angle_fix(info->pa);
	info->pd.x = cos(info->pa) * info->speed.rota;
	info->pd.y = sin(info->pa) * info->speed.rota;
}

void	ft_raycast(t_data *data)
{
	ft_dda(data);
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
	ft_raycast(data);
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
