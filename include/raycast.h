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

/*typedef struct s_info
{
	int		dist_off;
	int		mp;
	int		r;
	double	dist_h;
	double	dist_v;
	double	pa;
	double	ra;
	t_pos	off;
	t_poi	map;
	t_pos	pos;
	t_pos	pd;
	t_pos	r;
	t_pos	v;
}	t_info;*/

void	ft_test(t_data *data);
void	ft_raycast(t_data *game);
void	ft_draw_floor_and_sky(t_data *game);

#endif
