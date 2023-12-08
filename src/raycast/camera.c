#include "../../include/raycast.h"

static void	ft_camera_right(t_info *in)
{
	double	old_plane;
	double	old_dir;

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

static void	ft_camera_left(t_info *in)
{
	double	old_plane;
	double	old_dir;

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
