/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdelaros <wdelaros@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:50:28 by wdelaros          #+#    #+#             */
/*   Updated: 2023/12/08 16:50:29 by wdelaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parsing.h"

uint32_t	ft_rgba_to_uint(double r, double g, double b);
void		ft_init(t_data *data);
void		ft_raycast(t_data *data);
void		ft_hook(mlx_key_data_t keydata, void *param);

#endif