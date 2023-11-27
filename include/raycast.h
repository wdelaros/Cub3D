#ifndef RAYCAST_H
# define RAYCAST_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../include/error.h"
# include "../include/structure.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define UP 'u'
# define DOWN 'd'
# define LEFT 'l'
# define RIGHT 'r'
# define PI 3.1415926535
# define HALF_PI PI/2
# define P3 3*PI/2

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

void	ft_raycast(t_data *game);
void	ft_draw_floor_and_sky(t_data *game);

#endif
