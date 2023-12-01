#ifndef CUB3D_H
# define CUB3D_H

# include "parsing.h"

uint32_t	ft_rgba_to_uint(double r, double g, double b);
void		ft_init(t_data *data);
void		ft_raycast(t_data *data);
void		ft_hook(mlx_key_data_t keydata, void *param);

#endif