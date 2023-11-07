#ifndef RAYCAST_H
# define RAYCAST_H

# include <math.h>
# include "error.h"
# include <stdlib.h>
# include "structure.h"
# include "../libft/libft.h"

#define WIDTH 1024
#define HEIGHT 728

# ifndef ERROR_OUTPUT
#  define ERROR_OUTPUT 2
# endif
# ifndef TERM_OUTPUT
#  define TERM_OUTPUT 1
# endif

void	ft_raycast(t_data *game);
void	ft_draw_floor_and_sky(t_data *game);

#endif
