#ifndef STRUCTURE_H
# define STRUCTURE_H

# include "../MLX42/include/MLX42/MLX42.h"

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define UP 117
# define DOWN 100
# define LEFT 108
# define RIGHT 114
# define HITBOX 0.35

typedef struct s_sprite
{
	char	*path;
	xpm_t	*img;
	int		**pxl;
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
	double	move;
	double	rota;
}	t_speed;

typedef struct s_info
{
	t_pos			sd;
	t_pos			pos;
	t_pos			dir;
	t_pos			plane;
	t_pos			ray_dir;
	t_pos			delta_dist;
	t_poi			map;
	t_poi			step;
	double			pa;
	double			dist;
	double			time;
	double			camera_x;
	double			frametime;
	double			wall_dist;
	int				hit;
	int				side;
	int				line_h;
	int				wall_x;
	int				draw_end;
	int				draw_start;
	uint32_t		color;
	t_speed			speed;
}	t_info;

typedef struct s_data
{
	mlx_t		*mlx;
	t_info		*info;
	int			**map;
	char		**wall;
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
