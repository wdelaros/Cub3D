/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:52:02 by brheaume          #+#    #+#             */
/*   Updated: 2023/12/08 15:52:03 by brheaume         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../include/error.h"
# include "../include/structure.h"
# include "../MLX42/include/MLX42/MLX42.h"

# ifndef ERROR_OUTPUT
#  define ERROR_OUTPUT 2
# endif
# ifndef TERM_OUTPUT
#  define TERM_OUTPUT 1
# endif

# define BASE 4

void		ft_init(t_data *data);
void		ft_raycast(t_data *game);
int			**ft_xpm_convert(xpm_t *xpm);
void		ft_draw_limits(t_info *info);
void		ft_sky_and_floor(t_data *game);
void		ft_draw_texture(int x, t_data *data);
void		ft_raycast_calcs(int x, t_info *info);
void		ft_hero_move(t_data *data, char move);
void		ft_camera_move(t_data *data, char move);
uint32_t	ft_rgba_to_uint(double r, double g, double b);
void		ft_calculate_wall_x(xpm_t *wall, t_data *data);

#endif
