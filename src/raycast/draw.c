/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:51:04 by brheaume          #+#    #+#             */
/*   Updated: 2023/12/08 15:51:05 by brheaume         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/raycast.h"

static void	ft_sky(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(data->back, x, y, \
					ft_rgba_to_uint(
					data->c_sky.r,
					data->c_sky.g,
					data->c_sky.b));
			x++;
		}
		y++;
	}
}

static void	ft_floor(t_data *data)
{
	int	x;
	int	y;

	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(data->back, x, y, \
					ft_rgba_to_uint(
					data->c_floor.r,
					data->c_floor.g,
					data->c_floor.b));
			x++;
		}
		y++;
	}
}

void	ft_sky_and_floor(t_data *data)
{
	ft_sky(data);
	ft_floor(data);
}

static void	ft_draw_vertical(int x, t_data *data, xpm_t *wall, int **pxl)
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
		mlx_put_pixel(data->raycast, x, y, pxl[wall_y][data->info->wall_x]);
		y++;
	}
}

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
