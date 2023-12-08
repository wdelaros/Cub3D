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

void	ft_test(t_data *data);
void	ft_raycast(t_data *game);
void	ft_draw_floor_and_sky(t_data *game);
void	ft_draw_vertical(int x, t_data *data, xpm_t *wall, int **pxl);

#endif
