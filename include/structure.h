#ifndef STRUCTURE_H
# define STRUCTURE_H

# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_sprite
{
	char		*path;
	mlx_image_t	*img;
}	t_sprite;

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_poi
{
	int	x;
	int	y;
}	t_poi;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		set;
}	t_color;

typedef struct s_speed
{
	double move;
	double rota;
}	t_speed;

typedef struct s_info
{
	t_pos			sd;
	t_pos			pd;
	t_pos			pos;
	t_pos			dir;
	t_pos			plane;
	t_pos			ray_dir;
	t_pos			delta_dist;
	t_poi			map;
	t_poi			step;
	double			pa;
	double			time;
	double			camera_x;
	double			frametime;
	double			wall_dist;
	int				hit;
	int				side;
	int				line_h;
	int				draw_end;
	int				draw_start;
	unsigned int	color;
	t_speed	speed;
}	t_info;

typedef struct s_data
{
	mlx_t		*mlx;
	t_info		*info;
	char		**floor;
	char		**wall;
	char		**sky;
	t_color		c_floor;
	t_color		c_sky;
	t_pos		hero;
	t_sprite	north;
	t_sprite	south;
	t_sprite	west;
	t_sprite	east;
	mlx_image_t	*back;
	mlx_image_t	*raycast;
}	t_data;

#endif
