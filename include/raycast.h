#ifndef RAYCAST_H
# define RAYCAST_H

# include <math.h>
# include "error.h"
# include <stdlib.h>
# include "structure.h"
# include "../libft/libft.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define UP 'u'
#define DOWN 'd'
#define LEFT 'l'
#define RIGHT 'r'

# ifndef ERROR_OUTPUT
#  define ERROR_OUTPUT 2
# endif
# ifndef TERM_OUTPUT
#  define TERM_OUTPUT 1
# endif

typedef struct s_speed
{
	double move;
	double rotat;
}	t_speed;

/*typedef struct s_info
{
	t_pos	sd;
	t_pos	pos;
	t_pos	dir;
	t_pos	plane;
	t_pos	ray_dir;
	t_pos	delta_dist;
	t_posi	map;
	t_posi	step;
	double	time;
	double	camera_x;
	double	frametime;
	double	wall_dist;
	int		hit;
	int		side;
	int		draw_end;
	int		draw_start;
	int		line_h;
	t_speed	speed;
}	t_info;*/

typedef struct s_info
{
	double	pa;
	t_pos	pd;
	t_pos	pos;
}

void	ft_raycast(t_data *game);
void	ft_draw_floor_and_sky(t_data *game);

#endif
