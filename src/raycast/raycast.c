/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:51:38 by brheaume          #+#    #+#             */
/*   Updated: 2023/12/08 15:51:39 by brheaume         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/raycast.h"

static void	ft_step_direction(t_info *info)
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

static void	ft_dda(t_data *data)
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

static void	ft_wall_distance(t_info *info)
{
	if (info->side == 0)
		info->wall_dist = (info->sd.x - info->delta_dist.x);
	else
		info->wall_dist = (info->sd.y - info->delta_dist.y);
	info->line_h = (int)SCREEN_HEIGHT / info->wall_dist;
}

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE || keydata.key == MLX_KEY_Q)
			ft_error_interrupt(data);
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
	ft_bzero(data->raycast->pixels, \
			(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(int)));
	ft_raycast(data);
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
		x++;
	}
}
