#include <math.h>
#include "include/raycast.h"

t_info	ft_init_info(void)
{
	t_info	info;

	ft_bzero(&info,  sizeof(info));
	info.pos.x = 22;
	info.pos.y = 12;
	info.dir.x = -1;
	info.dir.y = 0;
	info.plane.x = 0;
	info.plane.y = 1;
	info.time = 0;
	info.hit = 0;
	info.side = 0;
	return (info);
}

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

void	ft_dda(t_info *info)
{
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
		if (info->worldMap[info->map.x][info->map.y] > 0)
			info->hit = 1;
	}
}

void	ft_draw_limits(t_info *info)
{
	info->draw_start = -(info->line_h) / 2 + SCREEN_HEIGHT / 2;
	info->draw_end = info->line_h / 2 + SCREEN_HEIGHT / 2;
	if (info->draw_start < 0)
		info->draw_start = 0;
	if (info->draw_end >= SCREEN_HEIGHT)
		info->draw_end = SCREEN_HEIGHT - 1;
}

void	ft_raycast_calcs(t_info *info)
{
	info->ray_dir.x = info->dir.x + info->plane.x * camera_x;
	info->ray_dir.y = info->dir.y + info->plane.y * camera_x;
	info->map.x = (int)info->pos.x;
	info->map.y = (int)info->pos.y;
	info->delta_dist.x = fabs(1 / info->ray_dir.x);
	info->delta_dist.y = fabs(1 / info->ray_dir.y);
}

void	ft_wall_distance(t_info *info)
{
	if (side == 0)
		info->wall_dist = (info->sd.x - delta_dist.x);
	else
		wall_dist = (info->sd.y - delta_dist.y);
	if (side == 1)
		color = color / 2;
}

void	ft_fps(t_info *info)
{
	double	old_time;

	old_time = info->time;
	time = mlx.delta_time;
	frametime = (time - old_time) / 1000.0;
	print(1.0 / frametime);
}

void	ft_set_speed(t_info *info)
{
	ft_fps(info);
	info->speed.move = info->frametime * 5.0;
	info->speed.rota = info->frametime * 3.0;
}

void	ft_hero_move(t_info *info, char move)
{
	int moved_x;
	int	moved_y;

	if (move == UP)
	{
		moved_x = info->pos.x + info->dir.x * info->speed.move;
		moved_y = info->pos.y + info->dir.y * info->speed.move;
		if (worldMap[(int)moved_x][(int)info->pos.y] == false)
			info->pos.x += info->dir.x * info->speed.move;
		if (worldMap[(int)info->pos.x][(int)moved_y] == false)
			info->pos.y += info->dir.y * info->speed.move;
	}
	if (move == DOWN)
	{
		moved_x = info->pos.x - info->dir.x * info->speed.move;
		moved_y = info->pos.y - info->dir.y * info->speed.move;
		if (worldMap[(int)moved_x][(int)info->pos.y] == false)
			info->pos.x -= info->dir.x * info->speed.move;
		if (worldMap[(int)info->pos.x][(int)moved_y] == false)
			info->pos.y -= info->dir.y * info->speed.move;
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

void	ft_camera_move(t_info *in,  char move)
{
	if (move == RIGHT)
		ft_camera_right(in);
	else if (move == LEFT)
		ft_camera_left(in);
}

void	ft_raycast(t_data *data)
{
	int	x;
	t_info *info;

	info = data->info;
	ft_set_speed(info);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		info->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		ft_raycast_calcs(info);
		ft_step_direction(info);
		ft_dda(info);
		ft_wall_distance(info);
		line_h = (int)(SCREEN_HEIGHT / wall_dist);
		ft_draw_limits(info);
		ft_set_texture(data);
		ft_draw_vertical(x, draw_start, draw_end, color);
	}
	/*redraw();*/
	//move this out 
	ft_hero_move();
	ft_camera_move();
}

int main(int ac,  char **av)
{
	t_info	info;

	info = ft_init_info();
	t_data.mlx = mlx_init(SCREEN_WIDTH,  SCREEN_HEIGHT,  "DINDE POMMES BACON",  false);
	while (hook)
		ft_raycast();
}
