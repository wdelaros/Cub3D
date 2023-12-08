#include "../../include/raycast.h"

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

void	ft_draw_limits(t_info *info)
{
	if (info->side % 2 == 0)
		info->wall_dist = (info->sd.x - info->delta_dist.x);
	else
		info->wall_dist = (info->sd.y - info->delta_dist.y);
	info->line_h = (int)(SCREEN_HEIGHT / info->wall_dist);
	info->draw_start = -(info->line_h) / 2 + SCREEN_HEIGHT / 2;
	info->draw_end = info->line_h / 2 + SCREEN_HEIGHT / 2;
	if (info->draw_start < 0)
		info->draw_start = 0;
	if (info->draw_end >= SCREEN_HEIGHT)
		info->draw_end = SCREEN_HEIGHT - 1;
}
