/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:51:31 by brheaume          #+#    #+#             */
/*   Updated: 2023/12/08 15:51:32 by brheaume         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/raycast.h"

static void	ft_move_up(t_info *info, int **map)
{
	double	moved_x;
	double	moved_y;

	moved_x = info->pos.x + info->dir.x * info->speed.move;
	moved_y = info->pos.y + info->dir.y * info->speed.move;
	if (map[(int)(moved_x + info->dir.x * HITBOX)][(int)info->pos.y] == false)
		info->pos.x = moved_x;
	if (map[(int)info->pos.x][(int)(moved_y + info->dir.y * HITBOX)] == false)
		info->pos.y = moved_y;
}

static void	ft_move_down(t_info *info, int **map)
{
	double	moved_x;
	double	moved_y;

	moved_x = info->pos.x - info->dir.x * info->speed.move;
	moved_y = info->pos.y - info->dir.y * info->speed.move;
	if (map[(int)(moved_x + info->dir.x * -HITBOX)][(int)info->pos.y] == false)
		info->pos.x = moved_x;
	if (map[(int)info->pos.x][(int)(moved_y + info->dir.y * -HITBOX)] == false)
		info->pos.y = moved_y;
}

static void	ft_move_left(t_info *info, int **map)
{
	double	moved_x;
	double	moved_y;

	moved_x = info->pos.x - info->dir.y * info->speed.move;
	moved_y = info->pos.y + info->dir.x * info->speed.move;
	if (map[(int)(moved_x + info->dir.y * HITBOX)][(int)info->pos.y] == false)
		info->pos.x = moved_x;
	if (map[(int)info->pos.x][(int)(moved_y + info->dir.x * HITBOX)] == false)
		info->pos.y = moved_y;
}

static void	ft_move_right(t_info *info, int **map)
{
	double	moved_x;
	double	moved_y;

	moved_x = info->pos.x + info->dir.y * info->speed.move;
	moved_y = info->pos.y - info->dir.x * info->speed.move;
	if (map[(int)(moved_x + info->dir.y * -HITBOX)][(int)info->pos.y] == false)
		info->pos.x = moved_x;
	if (map[(int)info->pos.x][(int)(moved_y + info->dir.x * -HITBOX)] == false)
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
